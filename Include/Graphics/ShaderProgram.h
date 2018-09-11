#pragma once

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include <string>

namespace winter {

	class ShaderProgram final {

	public:

		ShaderProgram(GLuint handle);
		~ShaderProgram();
		ShaderProgram(const ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		void use() const;
		void uploadMatrix(GLint location, const glm::mat4& matrix) const;

		GLuint getHandle() const;
		GLint getUniformLocation(const std::string& uniform) const;

	private:

		const GLuint handle;

	};

}