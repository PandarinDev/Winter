#include "Graphics/Texture.h"

namespace winter {

	Texture::Texture(GLuint handle, int width, int height)
		: handle(handle), width(width), height(height) {}

	Texture::~Texture() {
		glDeleteTextures(1, &handle);
	}

	void Texture::use(GLuint unit) const {
		glBindTextureUnit(unit, handle);
	}

	GLuint Texture::getHandle() const {
		return handle;
	}

	int Texture::getWidth() const {
		return width;
	}

	int Texture::getHeight() const {
		return height;
	}

}