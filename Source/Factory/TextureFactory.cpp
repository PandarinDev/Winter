#include "Factory/TextureFactory.h"
#include "External/stb_image.h"

#include <stdexcept>

namespace winter {

	std::unique_ptr<Texture> TextureFactory::createFromFile(const std::string& filePath) {
		GLuint handle;
		glCreateTextures(GL_TEXTURE_2D, 1, &handle);
		int width, height, components;
		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &components, 0);
		if (!data) {
			throw std::runtime_error("Failed to load texture '" + filePath + "'.");
		}
		glTextureStorage2D(handle, 1, GL_RGBA8, width, height);
		glTextureSubImage2D(handle, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
		glGenerateTextureMipmap(handle);
		glTextureParameteri(handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		return std::make_unique<Texture>(handle, width, height);
	}

}