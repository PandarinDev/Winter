#include "Factory/ShaderProgramFactory.h"
#include "Factory/ShaderFactory.h"

#include <stdexcept>

namespace winter {

	constexpr const char* ShaderProgramFactory::defaultVS_2D;
	constexpr const char* ShaderProgramFactory::defaultFS_2D;
	constexpr const char* ShaderProgramFactory::defaultVS_3D;
	constexpr const char* ShaderProgramFactory::defaultFS_3D;

	std::unique_ptr<ShaderProgram> ShaderProgramFactory::createDefault2DProgram() {
		std::vector<std::unique_ptr<Shader>> shaders;
		shaders.emplace_back(ShaderFactory::createFromSource(ShaderType::VERTEX_SHADER, defaultVS_2D));
		shaders.emplace_back(ShaderFactory::createFromSource(ShaderType::FRAGMENT_SHADER, defaultFS_2D));
		return createFromShaders(shaders);
	}

	std::unique_ptr<ShaderProgram> ShaderProgramFactory::createDefault3DProgram() {
		std::vector<std::unique_ptr<Shader>> shaders;
		shaders.emplace_back(ShaderFactory::createFromSource(ShaderType::VERTEX_SHADER, defaultVS_3D));
		shaders.emplace_back(ShaderFactory::createFromSource(ShaderType::FRAGMENT_SHADER, defaultFS_3D));
		return createFromShaders(shaders);
	}

	std::unique_ptr<ShaderProgram> ShaderProgramFactory::createFromShaders(const std::vector<std::unique_ptr<Shader>>& shaders) {
		GLuint handle = glCreateProgram();
		for (const auto& shader : shaders) {
			glAttachShader(handle, shader->getHandle());
		}
		glLinkProgram(handle);
		for (const auto& shader : shaders) {
			glDetachShader(handle, shader->getHandle());
		}
		GLint linkStatus;
		glGetProgramiv(handle, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE) {
			GLint infoLogLength;
			glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar* rawInfoLog = new GLchar[infoLogLength];
			glGetProgramInfoLog(handle, infoLogLength, nullptr, rawInfoLog);
			std::string infoLog(rawInfoLog);
			delete[] rawInfoLog;
			throw std::runtime_error("Failed to link shaderprogram: " + infoLog);
		}
		return std::make_unique<ShaderProgram>(handle);
	}

}