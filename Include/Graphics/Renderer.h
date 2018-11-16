#pragma once

#include "Graphics/Camera.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Mesh.h"
#include "Graphics/Font.h"
#include "Graphics/Framebuffer.h"
#include "Graphics/Texture.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <memory>
#include <vector>

namespace winter {

	class Renderer final {

	public:

		Renderer(
			const glm::vec3& clearColor,
			std::unique_ptr<ShaderProgram> shader2D,
			std::unique_ptr<ShaderProgram> shader3D,
			std::unique_ptr<ShaderProgram> shaderGBuffer,
			std::unique_ptr<Font> font,
			std::unique_ptr<Framebuffer> gBuffer,
			std::unique_ptr<Texture> defaultTexture,
			float fieldOfView,
			float perspectiveWidth,
			float perspectiveHeight,
			float perspectiveNear,
			float perspectiveFar);

		void beginFrame();
		void endFrame();
		void clearBuffers() const;
		void render(const std::shared_ptr<Text>& text);
		void render(const Mesh& mesh);

		Camera& getCamera();
		const ShaderProgram& getShaderProgram2D() const;
		const ShaderProgram& getShaderProgram3D() const;
		const Font& getFont() const;

		void setClearColor(const glm::vec3& clearColor);
		void setShaderProgram2D(std::unique_ptr<ShaderProgram> shader);
		void setShaderProgram3D(std::unique_ptr<ShaderProgram> shader);
		void setFont(std::unique_ptr<Font> font);

	private:

		static constexpr const char* PROJECTION_MATRIX_UNIFORM = "u_ProjectionMatrix";
		static constexpr const char* MODELVIEW_MATRIX_UNIFORM = "u_ModelViewMatrix";

		Camera camera;
		glm::mat4 projectionMatrix2D;
		glm::mat4 projectionMatrix3D;
		glm::mat4 modelViewMatrix;
		glm::vec3 clearColor;
		std::unique_ptr<ShaderProgram> shader2D;
		std::unique_ptr<ShaderProgram> shader3D;
		std::unique_ptr<ShaderProgram> shaderGBuffer;
		std::unique_ptr<Font> font;
		std::unique_ptr<Framebuffer> gBuffer;
		std::unique_ptr<Texture> defaultTexture;
		std::unique_ptr<Mesh> gBufferQuad;
		GLint projectionMatrixLocation;
		GLint modelViewMatrixLocation;
		std::vector<std::shared_ptr<Text>> textBuffer;

		void configureDefaults() const;
		void checkForErrors() const;

	};

}