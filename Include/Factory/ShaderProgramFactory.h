#pragma once

#include "Graphics/Shader.h"
#include "Graphics/ShaderProgram.h"

#include <vector>
#include <memory>

namespace winter {

	class ShaderProgramFactory final {

	public:

		static std::unique_ptr<ShaderProgram> createDefault2DProgram();
		static std::unique_ptr<ShaderProgram> createDefault3DProgram();
		static std::unique_ptr<ShaderProgram> createFromShaders(const std::vector<std::unique_ptr<Shader>>& shaders);

	private:

		static constexpr const char* defaultVS_2D = ""
			"#version 330 core\n"
			"uniform mat4 u_ProjectionMatrix;\n"
			"uniform mat4 u_ModelViewMatrix;\n"
			"layout (location = 0) in vec2 in_Position;\n"
			"layout (location = 1) in vec2 in_UV;\n"
			"out vec2 fs_UV;\n"
			"void main() {\n"
				"fs_UV = in_UV;\n"
				"gl_Position = u_ProjectionMatrix * vec4(in_Position, 0.0, 1.0);\n"
			"}\n";
		static constexpr const char* defaultFS_2D = ""
			"#version 330 core\n"
			"uniform sampler2D u_TexUnit;\n"
			"in vec2 fs_UV;\n"
			"layout (location = 0) out vec4 out_Color;\n"
			"void main() {\n"
				"out_Color = texture(u_TexUnit, vec2(fs_UV.x, fs_UV.y));"
			"}\n";

		static constexpr const char* defaultVS_3D = ""
			"#version 330 core\n"
			"uniform mat4 u_ProjectionMatrix;\n"
			"uniform mat4 u_ModelViewMatrix;\n"
			"layout (location = 0) in vec3 in_Position;\n"
			"layout (location = 1) in vec2 in_UV;\n"
			"layout (location = 2) in vec3 in_Normal;\n"
			"out vec3 fs_Normal;\n"
			"void main() {\n"
			"fs_Normal = in_Normal;\n"
			"gl_Position = u_ProjectionMatrix * u_ModelViewMatrix * vec4(in_Position, 1.0);\n"
			"}\n";
		static constexpr const char* defaultFS_3D = ""
			"#version 330 core\n"
			"in vec3 fs_Normal;\n"
			"layout (location = 0) out vec4 out_Color;\n"
			"void main() {\n"
			"out_Color = vec4(fs_Normal, 1.0);\n"
			"}\n";

	};

}