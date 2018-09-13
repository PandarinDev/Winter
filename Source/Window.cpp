#include "Window.h"

#include <stdexcept>

namespace winter {

	Window::Window(const std::string& title, int width, int height, bool vSync, bool fullScreen)
		: title(title), width(width), height(height), vSync(vSync), fullScreen(fullScreen) {
		configureHints();
		handle = glfwCreateWindow(
			width, height, title.c_str(),
			fullScreen ? glfwGetPrimaryMonitor() : nullptr,
			nullptr);
		if (!handle) {
			throw std::runtime_error("Failed to create window.");
		}
		makeCurrent();
		setVerticallySynchronized(vSync);
	}

	Window::~Window() {
		glfwDestroyWindow(handle);
	}

	void Window::makeCurrent() const {
		glfwMakeContextCurrent(handle);
	}

	void Window::pollEvents() const {
		glfwPollEvents();
	}

	void Window::swapBuffers() const {
		glfwSwapBuffers(handle);
	}

	bool Window::shouldClose() const {
		return glfwWindowShouldClose(handle);
	}

	void Window::setKeyCallback(GLFWkeyfun callback) const {
		glfwSetKeyCallback(handle, callback);
	}

	const std::string& Window::getTitle() const {
		return title;
	}

	int Window::getWidth() const {
		return width;
	}

	int Window::getHeight() const {
		return height;
	}

	bool Window::isVerticallySynchronized() const {
		return vSync;
	}

	bool Window::isFullScreen() const {
		return fullScreen;
	}

	void Window::setTitle(const std::string& title) {
		this->title = title;
		glfwSetWindowTitle(handle, title.c_str());
	}

	void Window::setSize(int width, int height) {
		this->width = width;
		this->height = height;
		glfwSetWindowSize(handle, width, height);
	}

	void Window::setVerticallySynchronized(bool vSync) {
		this->vSync = vSync;
		glfwSwapInterval(vSync ? 1 : 0);
	}

	void Window::setFullScreen(bool fullScreen) {
		this->fullScreen = fullScreen;
		glfwSetWindowMonitor(
			handle, fullScreen ? glfwGetPrimaryMonitor() : nullptr,
			0, 0, width, height, GLFW_DONT_CARE);
	}

	void Window::configureHints() const {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

}