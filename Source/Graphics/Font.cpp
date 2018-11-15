#include "Graphics/Font.h"
#include "Factory/MeshFactory.h"

namespace winter {

    Font::Font(const std::string &name, short size, unsigned short lineHeight, unsigned short base,
               std::unique_ptr<Texture> texture,
               std::unordered_map<FontChar::Id, FontChar>&& characters,
               std::unordered_map<std::pair<FontChar::Id, FontChar::Id>, short>&& kernings) :
               name(name), size(size), lineHeight(lineHeight), base(base), texture(texture.release()),
               characters(std::move(characters)), kernings(std::move(kernings)) {}

	std::unique_ptr<Text> Font::generateText(const std::string& content) const {
		static constexpr auto verticesPerCharacter = 24;
		std::vector<float> vertexBuffer(content.size() * verticesPerCharacter);
		std::size_t counter = 0;
		float cursorX = 0.0f, cursorY = 0.0f;
		float textureWidth = texture->getWidth();
		float textureHeight = texture->getHeight();
		FontChar::Id lastChar = -1u;
		for (const auto c : content) {
            auto fontChar = getFontChar(c);
			float x = cursorX + fontChar.xOffset;
			float y = cursorY;
			// Bottom right triangle
			vertexBuffer[counter++] = x;
			vertexBuffer[counter++] = y;
			vertexBuffer[counter++] = fontChar.x / textureWidth;
			vertexBuffer[counter++] = 1.0f - ((fontChar.y + fontChar.height) / textureHeight);

			vertexBuffer[counter++] = x + fontChar.width;
			vertexBuffer[counter++] = y;
			vertexBuffer[counter++] = (fontChar.x + fontChar.width) / textureWidth;
			vertexBuffer[counter++] = 1.0f - ((fontChar.y + fontChar.height) / textureHeight);

			vertexBuffer[counter++] = x + fontChar.width;
			vertexBuffer[counter++] = y + fontChar.height;
			vertexBuffer[counter++] = (fontChar.x + fontChar.width) / textureWidth;
			vertexBuffer[counter++] = 1.0f - (fontChar.y / textureHeight);
			// Upper left triangle
			vertexBuffer[counter++] = x;
			vertexBuffer[counter++] = y;
			vertexBuffer[counter++] = fontChar.x / textureWidth;
			vertexBuffer[counter++] = 1.0f - ((fontChar.y + fontChar.height) / textureHeight);

			vertexBuffer[counter++] = x + fontChar.width;
			vertexBuffer[counter++] = y + fontChar.height;
			vertexBuffer[counter++] = (fontChar.x + fontChar.width) / textureWidth;
			vertexBuffer[counter++] = 1.0f - (fontChar.y / textureHeight);

			vertexBuffer[counter++] = x;
			vertexBuffer[counter++] = y + fontChar.height;
			vertexBuffer[counter++] = fontChar.x / textureWidth;
			vertexBuffer[counter++] = 1.0f - (fontChar.y / textureHeight);

            cursorX += fontChar.xAdvance;
			auto kerningIt = kernings.find(std::make_pair(lastChar, fontChar.id));
			if (kerningIt != kernings.end()) {
				cursorX += kerningIt->second;
			}
			lastChar = fontChar.id;
		}

		std::vector<VertexAttribute> attributes = {
                { 0, 2 }, // Geometry
                { 1, 2 }  // Texture coordinates
		};
        return std::make_unique<Text>(MeshFactory::loadGeometry(vertexBuffer, attributes), texture);
	}

    const std::string& Font::getName() const {
        return name;
    }

    short Font::getSize() const {
        return size;
    }

    unsigned short Font::getLineHeight() const {
        return lineHeight;
    }

    unsigned short Font::getBase() const {
        return base;
    }

    const Texture& Font::getTexture() const {
        return *texture;
    }

    const FontChar& Font::getFontChar(winter::FontChar::Id id) const {
        return characters.at(id);
    }

    short Font::getKerningForPair(winter::FontChar::Id first, winter::FontChar::Id second) const {
        return kernings.at(std::make_pair(first, second));
    }

}