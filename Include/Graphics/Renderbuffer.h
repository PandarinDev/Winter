#pragma once

#include "External/glad.h"

namespace winter {

	class Renderbuffer final {

	public:

		Renderbuffer(GLuint handle);
		~Renderbuffer();
		Renderbuffer(const Renderbuffer&) = delete;
		Renderbuffer& operator=(const Renderbuffer&) = delete;

		GLuint getHandle() const;

	private:

		const GLuint handle;

	};

}