#include "Graphics/Renderer.h"
#include "Utility/OGLUtils.h"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <stdexcept>

namespace winter {

	constexpr const char* Renderer::PROJECTION_MATRIX_UNIFORM;
	constexpr const char* Renderer::MODELVIEW_MATRIX_UNIFORM;

	Renderer::Renderer(
		const glm::vec3& clearColor,
		std::unique_ptr<ShaderProgram> shader,
		float perspectiveWidth,
		float perspectiveHeight) :
			projectionMatrix(glm::ortho(0.0f, perspectiveWidth, 0.0f, perspectiveHeight)),
			modelViewMatrix(glm::mat4(1.0f)),
			rendering(false) {
		configureDefaults();
		setupBuffers();
		setClearColor(clearColor);
		setShaderProgram(std::move(shader));
	}

	void Renderer::clearBuffers() const {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::beginFrame() {
		rendering = true;
		geometryBuffer.clear();
	}

	void Renderer::render(const Geometry& geometry) {
		geometryBuffer.insert(geometryBuffer.end(), geometry.begin(), geometry.end());
	}

	void Renderer::finishFrame() {
		rendering = false;
		shader->uploadMatrix(projectionMatrixLocation, projectionMatrix);
		shader->uploadMatrix(modelViewMatrixLocation, modelViewMatrix);
		glNamedBufferData(vbo, geometryBuffer.size() * sizeof(float), geometryBuffer.data(), GL_STREAM_DRAW);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, geometryBuffer.size() / 2);
		checkForErrors();
	}

	const ShaderProgram& Renderer::getShaderProgram() const {
		return *shader;
	}

	void Renderer::setClearColor(const glm::vec3& clearColor) {
		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
	}

	void Renderer::setShaderProgram(std::unique_ptr<ShaderProgram> shader) {
		this->shader = std::move(shader);
		this->shader->use();
		projectionMatrixLocation = this->shader->getUniformLocation(PROJECTION_MATRIX_UNIFORM);
		modelViewMatrixLocation = this->shader->getUniformLocation(MODELVIEW_MATRIX_UNIFORM);
	}

	void Renderer::configureDefaults() const {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::setupBuffers() {
		glCreateVertexArrays(1, &vao);
		glCreateBuffers(1, &vbo);
		glEnableVertexArrayAttrib(vao, 0);
		glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayVertexBuffer(vao, 0, vbo, 0, 2 * sizeof(float));
	}

	void Renderer::checkForErrors() const {
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::string errorMessage = OGLUtils::translateErrorCode(error);
			throw std::runtime_error("Rendering API error: " + errorMessage);
		}
	}

}