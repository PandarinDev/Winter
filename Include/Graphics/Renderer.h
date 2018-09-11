#pragma once

#include "Graphics/ShaderProgram.h"
#include "Graphics/Geometry.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <memory>

namespace winter {

	class Renderer final {

	public:

		Renderer(
			const glm::vec3& clearColor,
			std::unique_ptr<ShaderProgram> shader,
			float perspectiveWidth,
			float perspectiveHeight);

		void clearBuffers() const;
		void beginFrame();
		void render(const Geometry& geometry);
		void finishFrame();

		const ShaderProgram& getShaderProgram() const;

		void setClearColor(const glm::vec3& clearColor);
		void setShaderProgram(std::unique_ptr<ShaderProgram> shader);

	private:

		static constexpr const char* PROJECTION_MATRIX_UNIFORM = "u_ProjectionMatrix";
		static constexpr const char* MODELVIEW_MATRIX_UNIFORM = "u_ModelViewMatrix";

		glm::mat4 projectionMatrix;
		glm::mat4 modelViewMatrix;
		GLuint vao;
		GLuint vbo;
		bool rendering;
		glm::vec3 clearColor;
		std::unique_ptr<ShaderProgram> shader;
		GLint projectionMatrixLocation;
		GLint modelViewMatrixLocation;
		Geometry geometryBuffer;

		void configureDefaults() const;
		void setupBuffers();
		void checkForErrors() const;

	};

}