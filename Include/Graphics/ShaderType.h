#pragma once

#include <GL/glew.h>

namespace winter {

	enum class ShaderType : GLenum {
		VERTEX_SHADER = GL_VERTEX_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	};

}