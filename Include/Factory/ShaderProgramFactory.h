#pragma once

#include "Graphics/Shader.h"
#include "Graphics/ShaderProgram.h"

#include <vector>
#include <memory>

namespace winter {

	class ShaderProgramFactory final {

	public:

		static std::unique_ptr<ShaderProgram> createDefaultProgram();
		static std::unique_ptr<ShaderProgram> createFromShaders(const std::vector<std::unique_ptr<Shader>>& shaders);

	private:

		static constexpr const char* defaultVS = ""
			"#version 330 core\n"
			"uniform mat4 u_ProjectionMatrix;\n"
			"uniform mat4 u_ModelViewMatrix;\n"
			"layout (location = 0) in vec3 in_Position;\n"
			"void main() {\n"
			"gl_Position = u_ProjectionMatrix * u_ModelViewMatrix * vec4(in_Position, 1.0);\n"
			"}\n";
		static constexpr const char* defaultFS = ""
			"#version 330 core\n"
			"layout (location = 0) out vec4 out_Color;\n"
			"void main() {\n"
			"out_Color = vec4(1.0, 0.0, 0.0, 1.0);\n"
			"}\n";

	};

}