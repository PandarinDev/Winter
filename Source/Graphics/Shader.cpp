#include "Graphics/Shader.h"

namespace winter {

	Shader::Shader(GLuint handle) : handle(handle) {}

	Shader::~Shader() {
		glDeleteShader(handle);
	}

	GLuint Shader::getHandle() const {
		return handle;
	}

}