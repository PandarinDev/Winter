#pragma once

#include <GLFW/glfw3.h>

#include <string>

namespace winter {

	class Window final {

	public:

		Window(const std::string& title, int width, int height, bool vSync, bool fullScreen);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		void makeCurrent() const;
		void pollEvents() const;
		void swapBuffers() const;
		bool shouldClose() const;
		void captureCursor() const;
		void releaseCursor() const;
		void setKeyCallback(GLFWkeyfun callback) const;
		void setMouseCallback(GLFWcursorposfun callback) const;

		const std::string& getTitle() const;
		int getWidth() const;
		int getHeight() const;
		bool isVerticallySynchronized() const;
		bool isFullScreen() const;

		void setTitle(const std::string& title);
		void setSize(int width, int height);
		void setVerticallySynchronized(bool vSync);
		void setFullScreen(bool fullScreen);

	private:

		GLFWwindow * handle;
		std::string title;
		int width;
		int height;
		bool vSync;
		bool fullScreen;

		void configureHints() const;

	};

}