#include "Factory/ShaderFactory.h"
#include "Utility/TypeUtils.h"

#include <stdexcept>

namespace winter {
	
	std::unique_ptr<Shader> ShaderFactory::createFromSource(ShaderType type, const std::string& source) {
		GLuint handle = glCreateShader(TypeUtils::enumValue(type));
		const char* source_ptr = source.c_str();
		glShaderSource(handle, 1, &source_ptr, nullptr);
		glCompileShader(handle);
		GLint compilationStatus;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &compilationStatus);
		if (compilationStatus != GL_TRUE) {
			GLint infoLogLength;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar* rawInfoLog = new GLchar[infoLogLength];
			glGetShaderInfoLog(handle, infoLogLength, nullptr, rawInfoLog);
			std::string infoLog(rawInfoLog);
			delete[] rawInfoLog;
			throw std::runtime_error("Failed to compile shader: " + infoLog);
		}
		return std::make_unique<Shader>(handle);
	}

}