#include "Graphics/ShaderProgram.h"

#include <stdexcept>

namespace winter {

	ShaderProgram::ShaderProgram(GLuint handle) : handle(handle) {}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(handle);
	}

	void ShaderProgram::use() const {
		glUseProgram(handle);
	}

	void ShaderProgram::uploadMatrix(GLint location, const glm::mat4& matrix) const {
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}

	GLuint ShaderProgram::getHandle() const {
		return handle;
	}

	GLint ShaderProgram::getUniformLocation(const std::string& uniform) const {
		static constexpr auto UNIFORM_NOT_FOUND_VALUE = -1;
		GLint location = glGetUniformLocation(handle, uniform.c_str());
		if (location == UNIFORM_NOT_FOUND_VALUE) {
			throw std::runtime_error("Uniform '" + uniform + "' was not found in shaderprogram.");
		}
		return location;
	}

}