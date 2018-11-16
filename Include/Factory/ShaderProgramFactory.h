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
		static std::unique_ptr<ShaderProgram> createDefaultGBufferProgram();
		static std::unique_ptr<ShaderProgram> createFromShaders(const std::vector<std::unique_ptr<Shader>>& shaders);

	private:

		// Default 2D program
		static constexpr const char* defaultVS_2D = ""
			"#version 330 core\n"
			"uniform mat4 u_ProjectionMatrix;\n"
			"uniform mat4 u_ModelViewMatrix;\n"
			"layout (location = 0) in vec2 in_Position;\n"
			"layout (location = 1) in vec2 in_UV;\n"
			"out vec2 fs_UV;\n"
			"void main() {\n"
				"fs_UV = in_UV;\n"
				"gl_Position = u_ProjectionMatrix * u_ModelViewMatrix * vec4(in_Position, 0.0, 1.0);\n"
			"}\n";
		static constexpr const char* defaultFS_2D = ""
			"#version 330 core\n"
			"uniform sampler2D u_TexUnit;\n"
			"in vec2 fs_UV;\n"
			"layout (location = 0) out vec4 out_Color;\n"
			"void main() {\n"
			"out_Color = texture(u_TexUnit, fs_UV);"
			"}\n";

		// Default 3D program
		static constexpr const char* defaultVS_3D = ""
			"#version 330 core\n"
			"uniform mat4 u_ProjectionMatrix;\n"
			"uniform mat4 u_ModelViewMatrix;\n"
			"layout (location = 0) in vec3 in_Position;\n"
			"layout (location = 1) in vec2 in_UV;\n"
			"layout (location = 2) in vec3 in_Normal;\n"
			"out vec4 fs_Position;\n"
			"out vec2 fs_UV;\n"
			"out vec4 fs_Normal;\n"
			"void main() {\n"
			"fs_Position = u_ModelViewMatrix * vec4(in_Position, 1.0);\n"
			"fs_UV = in_UV;\n"
			"fs_Normal = u_ModelViewMatrix * vec4(in_Normal, 1.0);\n"
			"gl_Position = u_ProjectionMatrix * u_ModelViewMatrix * vec4(in_Position, 1.0);\n"
			"}\n";
		static constexpr const char* defaultFS_3D = ""
			"#version 330 core\n"
			"uniform sampler2D u_TexUnit;\n"
			"in vec4 fs_Position;\n"
			"in vec2 fs_UV;\n"
			"in vec4 fs_Normal;\n"
			"layout (location = 0) out vec4 out_Position;\n"
			"layout (location = 1) out vec4 out_Normal;\n"
			"layout (location = 2) out vec4 out_Diffuse;\n"
			"void main() {\n"
			"out_Position = fs_Position;\n"
			"out_Normal = fs_Normal;\n"
			"out_Diffuse = texture(u_TexUnit, fs_UV);\n"
			"}\n";

		// Default GBuffer program
		static constexpr const char* defaultVS_GBuffer = ""
			"#version 330 core\n"
			"uniform mat4 u_ProjectionMatrix;\n"
			"layout (location = 0) in vec2 in_Position;\n"
			"layout (location = 1) in vec2 in_UV;\n"
			"out vec2 fs_UV;\n"
			"void main() {\n"
			"fs_UV = in_UV;\n"
			"gl_Position = u_ProjectionMatrix * vec4(in_Position, 0.0, 1.0);\n"
			"}\n";
		static constexpr const char* defaultFS_GBuffer = ""
			"#version 420 core\n"
			"layout (binding = 0) uniform sampler2D u_TexPosition;\n"
			"layout (binding = 1) uniform sampler2D u_TexNormal;\n"
			"layout (binding = 2) uniform sampler2D u_Diffuse;\n"
			"in vec2 fs_UV;\n"
			"layout (location = 0) out vec4 out_Color;\n"
			"void main() {\n"
			"vec3 position = texture(u_TexPosition, fs_UV).xyz;\n"
			"vec3 normal = texture(u_TexNormal, fs_UV).xyz;\n"
			"vec4 diffuse = texture(u_Diffuse, fs_UV);\n"
			"out_Color = diffuse * 0.3;\n"
			"}\n";

	};

}