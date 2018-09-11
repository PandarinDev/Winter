// Important: GLEW must be included before GLFW.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Graphics/Renderer.h"
#include "Factory/ShaderProgramFactory.h"

#include <stdexcept>

void initGLFW() {
	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW.");
	}
}

void initGLEW() {
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Failed to initialize GLEW.");
	}
}

int main(int argc, char** argv) {
	using namespace winter;
	initGLFW();
	Window window("Winter v0.1", 1600, 900, true, false);
	initGLEW();
	Renderer renderer(glm::vec3(0.1f, 0.5f, 0.95f), ShaderProgramFactory::createDefaultProgram(), 1600.f, 900.f);
	Geometry triangle{
		0.0f, 0.0f,
		300.0f, 0.0f,
		0.0f, 300.0f
	};
	while (!window.shouldClose()) {
		window.pollEvents();
		renderer.clearBuffers();
		renderer.beginFrame();
		renderer.render(triangle);
		renderer.finishFrame();
		window.swapBuffers();
	}
	return 0;
}