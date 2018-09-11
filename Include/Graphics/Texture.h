#pragma once

#include <GL/glew.h>

namespace winter {

	class Texture final {

	public:

		Texture(GLuint handle, int width, int height);
		~Texture();
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		GLuint getHandle() const;
		int getWidth() const;
		int getHeight() const;

	private:

		const GLuint handle;
		const int width;
		const int height;

	};

}