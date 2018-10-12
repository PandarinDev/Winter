// Important: GLAD must be included before GLFW
#include "External/glad.h"
#include "GLFW/glfw3.h"

#include "Window.h"
#include "Input/InputManager.h"
#include "Graphics/Renderer.h"
#include "Factory/MeshFactory.h"
#include "Factory/ShaderProgramFactory.h"

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

#include <iostream>
#include <stdexcept>

void initGLFW() {
	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW.");
	}
}

void initGLAD() {
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

int main(int argc, char** argv) {
	using namespace winter;
	initGLFW();
	Window window("Winter v0.1", 1600, 900, true, false);
	window.captureCursor();
	auto& inputManager = InputManager::getInstance();
	inputManager.hookInto(window);
	initGLAD();
	Renderer renderer(
		glm::vec3(0.1f, 0.5f, 0.95f),
		ShaderProgramFactory::createDefaultProgram(),
		glm::radians(60.0f),
		1600.f, 900.f, 0.1f, 100.0f);
	auto dragonPtr = MeshFactory::loadFile(MeshFormat::OBJ, "Assets/Meshes/DragonWithNormals.obj");
	auto& camera = renderer.getCamera();
	static constexpr float cameraSpeed = 0.05f;
	inputManager.registerEventListener(KeyEvent::KEY_DOWN, [&camera](int keyCode) {
		glm::vec3 translation(0.0f, 0.0f, 0.0f);
		switch (keyCode) {
		case GLFW_KEY_A:
			translation = glm::vec3(-1.0f, 0.0f, 0.0f);
			break;
		case GLFW_KEY_D:
			translation = glm::vec3(1.0f, 0.0f, 0.0f);
			break;
		case GLFW_KEY_W:
			translation = camera.getDirection();
			break;
		case GLFW_KEY_S:
			translation = -camera.getDirection();
			break;
		case GLFW_KEY_Q:
			translation = glm::vec3(0.0f, -1.0f, 0.0f);
			break;
		case GLFW_KEY_E:
			translation = glm::vec3(0.0f, 1.0f, 0.0f);
			break;
		}
		camera.translate(translation * cameraSpeed);
	});

	glm::vec2 lastMousePos;
	static constexpr float mouseSensitivity = 0.1f;
	while (!window.shouldClose()) {
		window.pollEvents();
		InputManager::getInstance().tick();
		const glm::vec2& mousePos = inputManager.getMousePosition();
		glm::vec2 mouseDelta = mousePos - lastMousePos;
		glm::vec3 cameraDir = renderer.getCamera().getDirection();
		cameraDir = glm::rotateX(cameraDir, -glm::radians(mouseDelta.y) * mouseSensitivity);
		cameraDir = glm::rotateY(cameraDir, -glm::radians(mouseDelta.x) * mouseSensitivity);
		renderer.getCamera().setDirection(cameraDir);
		lastMousePos = mousePos;
		renderer.clearBuffers();
		renderer.render(*dragonPtr);
		window.swapBuffers();
	}
	return 0;
}