// Important: GLAD must be included before GLFW
#include "External/glad.h"
#include "GLFW/glfw3.h"

#include "Window.h"
#include "Input/InputManager.h"
#include "Input/CameraInputHandler.h"
#include "Graphics/Renderer.h"
#include "Factory/MeshFactory.h"
#include "Factory/ShaderProgramFactory.h"

#include "glm/glm.hpp"

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
	inputManager.registerEventListener(KeyEvent::KEY_DOWN, std::make_unique<CameraKeyInputHandler>(camera));
	inputManager.registerMouseListener(std::make_unique<CameraMouseInputHandler>(camera));
	while (!window.shouldClose()) {
		window.pollEvents();
		InputManager::getInstance().tick();
		// Render and swap buffers
		renderer.clearBuffers();
		renderer.render(*dragonPtr);
		window.swapBuffers();
	}
	return 0;
}