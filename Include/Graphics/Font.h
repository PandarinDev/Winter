#pragma once

#include "Graphics/FontChar.h"
#include "Graphics/Texture.h"
#include "Graphics/Text.h"

#include <string>
#include <unordered_map>
#include <memory>

namespace std {

    template<>
    struct hash<std::pair<winter::FontChar::Id, winter::FontChar::Id>> {

        std::size_t operator()(const std::pair<winter::FontChar::Id, winter::FontChar::Id>& k) const {
            std::size_t hash = 5;
            hash = 29 * hash + k.first;
            hash = 29 * hash + k.second;
            return hash;
        }

    };

}

namespace winter {

    class Font final {

    public:

        Font(const std::string& name, short size,
                unsigned short lineHeight, unsigned short base,
                std::unique_ptr<Texture> texture, std::unordered_map<FontChar::Id, FontChar>&& characters,
                std::unordered_map<std::pair<FontChar::Id, FontChar::Id>, short>&& kernings);

		std::unique_ptr<Text> generateText(const std::string& content) const;

        const std::string& getName() const;
        short getSize() const;
        unsigned short getLineHeight() const;
        unsigned short getBase() const;
        const Texture& getTexture() const;
        const FontChar& getFontChar(FontChar::Id id) const;
        short getKerningForPair(FontChar::Id first, FontChar::Id second) const;

    private:

        std::string name;
        short size;
        unsigned short lineHeight;
        unsigned short base;
        std::shared_ptr<Texture> texture;
        std::unordered_map<FontChar::Id, FontChar> characters;
        std::unordered_map<std::pair<FontChar::Id, FontChar::Id>, short> kernings;

    };

}