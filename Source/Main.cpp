// Important: GLAD must be included before GLFW
#include "External/glad.h"
#include <GLFW/glfw3.h>

#include "Window.h"
#include "Graphics/Renderer.h"
#include "Factory/ShaderProgramFactory.h"

#include <glm/glm.hpp>

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
	initGLAD();
	Renderer renderer(
		glm::vec3(0.1f, 0.5f, 0.95f),
		ShaderProgramFactory::createDefaultProgram(),
		glm::radians(60.0f),
		1600.f, 900.f, 0.1f, 100.0f);
	Geometry triangle{
		0.0f, 0.0f, -10.0f,
		1.5f, 0.0f, -10.0f,
		0.75f, 1.5f, -10.0f
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