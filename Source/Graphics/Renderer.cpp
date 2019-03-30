#include "Graphics/Renderer.h"
#include "Graphics/Quad.h"
#include "Utility/OGLUtils.h"
#include "External/glad.h"
#include "Factory/MeshFactory.h"

#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <stdexcept>

namespace winter {

	constexpr const char* Renderer::PROJECTION_MATRIX_UNIFORM;
	constexpr const char* Renderer::MODELVIEW_MATRIX_UNIFORM;

	Renderer::Renderer(
		const glm::vec3& clearColor,
		std::unique_ptr<ShaderProgram> shader2D,
		std::unique_ptr<ShaderProgram> shader3D,
		std::unique_ptr<Font> font,
		std::unique_ptr<Texture> defaultTexture,
		float fieldOfView,
		float perspectiveWidth,
		float perspectiveHeight,
		float perspectiveNear,
		float perspectiveFar) :
			projectionMatrix2D(glm::ortho(0.0f, perspectiveWidth, 0.0f, perspectiveHeight)),
			projectionMatrix3D(glm::perspective(fieldOfView, perspectiveWidth / perspectiveHeight, perspectiveNear, perspectiveFar)),
			modelViewMatrix(glm::mat4(1.0f)), defaultTexture(std::move(defaultTexture)) {
		configureDefaults();
		setClearColor(clearColor);
		setShaderProgram2D(std::move(shader2D));
		setShaderProgram3D(std::move(shader3D));
		setFont(std::move(font));
	}

	void Renderer::beginFrame() {
		clearBuffers();
	}

	void Renderer::endFrame() {
		glDisable(GL_DEPTH_TEST);
		// Render queued 2D elements on top of 3D elements
		shader2D->use();
		projectionMatrixLocation = shader2D->getUniformLocation(PROJECTION_MATRIX_UNIFORM);
		modelViewMatrixLocation = shader2D->getUniformLocation(MODELVIEW_MATRIX_UNIFORM);
		for (const auto& text : textBuffer) {
			glBindVertexArray(text->getMesh().getVertexArrayObject());
			text->getTexture().use(0);
			shader2D->uploadMatrix(projectionMatrixLocation, projectionMatrix2D);
			shader2D->uploadMatrix(modelViewMatrixLocation, text->getMesh().getTransformations());
			glDrawArrays(GL_TRIANGLES, 0, text->getMesh().getNumberOfIndices());
		}
		textBuffer.clear();
		checkForErrors();
	}

	void Renderer::clearBuffers() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::render(const std::shared_ptr<Text>& text) {
		textBuffer.emplace_back(text);
	}

	void Renderer::render(const Mesh& mesh) {
		glEnable(GL_DEPTH_TEST);
		glBindVertexArray(mesh.getVertexArrayObject());
		shader3D->use();
		defaultTexture->use(0);
		auto projectionMatrixLocation = shader3D->getUniformLocation("u_ProjectionMatrix");
		auto modelMatrixLocation = shader3D->getUniformLocation("u_ModelMatrix");
		auto viewMatrixLocation = shader3D->getUniformLocation("u_ViewMatrix");
		shader3D->uploadMatrix(projectionMatrixLocation, projectionMatrix3D);
		shader3D->uploadMatrix(modelMatrixLocation, mesh.getTransformations());
		shader3D->uploadMatrix(viewMatrixLocation, camera.calculateTransformationMatrix());
		glDrawArrays(GL_TRIANGLES, 0, mesh.getNumberOfIndices());
		checkForErrors();
	}

	Camera& Renderer::getCamera() {
		return camera;
	}

	const ShaderProgram& Renderer::getShaderProgram2D() const {
		return *shader2D;
	}

	const ShaderProgram& Renderer::getShaderProgram3D() const {
		return *shader3D;
	}

	const Font& Renderer::getFont() const {
		return *font;
	}

	void Renderer::setClearColor(const glm::vec3& clearColor) {
		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
	}

	void Renderer::setShaderProgram2D(std::unique_ptr<winter::ShaderProgram> shader) {
		this->shader2D = std::move(shader);
	}

	void Renderer::setShaderProgram3D(std::unique_ptr<ShaderProgram> shader) {
		this->shader3D = std::move(shader);
	}

	void Renderer::setFont(std::unique_ptr<Font> font) {
        this->font = std::move(font);
	}

	void Renderer::configureDefaults() const {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::checkForErrors() const {
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::string errorMessage = OGLUtils::translateErrorCode(error);
			throw std::runtime_error("Rendering API error: " + errorMessage);
		}
	}

}