#include "Factory/FontFactory.h"
#include "Factory/TextureFactory.h"
#include "Graphics/FontChar.h"
#include "Utility/FileUtils.h"

#include <vector>
#include <fstream>
#include <stdexcept>
#include <cstdint>
#include <string_view>

namespace winter {

    /**
     * Reads a fixed number of characters from the buffer starting at the given offset.
     */
    std::string_view readString(const std::vector<char>& buffer, int offset, int chars) {
        return std::string_view(buffer.data() + offset, chars);
    }

    /**
     * Reads a null terminated string from the buffer starting at the given offset.
     */
    std::string_view readString(const std::vector<char>& buffer, int offset) {
        int endOffset = offset;
		for (char c = buffer[endOffset]; c != '\0'; c = buffer[++endOffset]);
        return std::string_view(buffer.data() + offset, endOffset - offset);
    }

    /**
     * Reads the supplied type from the buffer starting at the given offset.
     */
    template<typename T>
    T& readType(std::vector<char>& buffer, int offset) {
        return *reinterpret_cast<T*>(buffer.data() + offset);
    }

    std::unique_ptr<Font> FontFactory::createFromFile(const std::string& filePath) {
        std::ifstream inputFile(filePath, std::ios::binary);
        if (!inputFile) {
            throw std::runtime_error("Failed to open input file '" + filePath + "'.");
        }
        std::vector<char> buffer(std::istreambuf_iterator<char>(inputFile), {});
        inputFile.close();

        // Verify input file header and version
        std::string_view header = readString(buffer, 0, 3);
        if (header != "BMF") {
            throw std::runtime_error("Input file is of invalid format.");
        }
        auto version = readType<std::int8_t>(buffer, 3);
        if (version != 3) {
            throw std::runtime_error("Input file is of invalid version.");
        }
        // Read first block data (font metadata)
        auto firstBlockSize = readType<std::int32_t>(buffer, 5);
        auto firstBlockOffset = 5 + sizeof(firstBlockSize);
        // Read data fields (most of them are ignored)
        auto fontSize = readType<std::int16_t>(buffer, firstBlockOffset + 0);
        auto fontName = readString(buffer, firstBlockOffset + 14);

        // Read second block data (font metadata)
        auto secondBlockSize = readType<std::int32_t>(buffer, firstBlockOffset + firstBlockSize + 1);
        auto secondBlockOffset = firstBlockOffset + firstBlockSize + 1 + sizeof(secondBlockSize);
        auto lineHeight = readType<std::uint16_t>(buffer, secondBlockOffset + 0);
        auto base = readType<std::uint16_t>(buffer, secondBlockOffset + 2);

        // Read third block data (pages)
        auto thirdBlockSize = readType<std::int32_t>(buffer, secondBlockOffset + secondBlockSize + 1);
        auto thirdBlockOffset = secondBlockOffset + secondBlockSize + 1 + sizeof(thirdBlockSize);
        auto pageName = readString(buffer, thirdBlockOffset + 0);
        if (pageName.size() + 1 != thirdBlockSize) {
            throw std::runtime_error("Multiple pages are not supported in the input.");
        }
        auto texture = TextureFactory::createFromFile(FileUtils::getParent(filePath) + "/" + pageName.data());

        // Read fourth block data (characters)
        auto fourthBlockSize = readType<std::int32_t>(buffer, thirdBlockOffset + thirdBlockSize + 1);
        auto fourthBlockOffset = thirdBlockOffset + thirdBlockSize + 1 + sizeof(fourthBlockSize);
        std::unordered_map<FontChar::Id, FontChar> fontCharacters;
        for (int byteCounter = 0; byteCounter < fourthBlockSize; byteCounter += 20) {
            auto offset = fourthBlockOffset + byteCounter;
            auto charId = readType<std::uint32_t>(buffer, offset + 0);
            auto charX = readType<std::uint16_t>(buffer, offset + 4);
            auto charY = readType<std::uint16_t>(buffer, offset + 6);
            auto charWidth = readType<std::uint16_t>(buffer, offset + 8);
            auto charHeight = readType<std::uint16_t>(buffer, offset + 10);
            auto charXOffset = readType<std::int16_t>(buffer, offset + 12);
            auto charYOffset = readType<std::int16_t>(buffer, offset + 14);
            auto charXAdvance = readType<std::int16_t>(buffer, offset + 16);
            fontCharacters.emplace(std::piecewise_construct,
                    std::forward_as_tuple(charId),
                    std::forward_as_tuple(charId, charX, charY, charWidth, charHeight, charXOffset, charYOffset, charXAdvance));
        }

        // Read fifth block data (kerning pairs)
        std::unordered_map<std::pair<FontChar::Id, FontChar::Id>, short> kernings;
        bool hasKerning = buffer.size() > fourthBlockOffset + fourthBlockSize + 1;
        if (hasKerning) {
            auto fifthBlockSize = readType<std::int32_t>(buffer, fourthBlockOffset + fourthBlockSize + 1);
            auto fifthBlockOffset = fourthBlockOffset + fourthBlockSize + 1 + sizeof(fifthBlockSize);
            for (int byteCounter = 0; byteCounter < fifthBlockSize; byteCounter += 10) {
                auto offset = fifthBlockOffset + byteCounter;
                auto first = readType<std::uint32_t>(buffer, offset + 0);
                auto second = readType<std::uint32_t>(buffer, offset + 4);
                auto kerning = readType<std::int16_t>(buffer, offset + 8);
                kernings.emplace(std::piecewise_construct, std::forward_as_tuple(first, second), std::forward_as_tuple(kerning));
            }
        }

        return std::make_unique<Font>(
                fontName.data(), fontSize, lineHeight, base, std::move(texture), std::move(fontCharacters), std::move(kernings));
    }

}