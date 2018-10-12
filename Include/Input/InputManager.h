#pragma once

#include "Window.h"

#include "glm/vec2.hpp"
#include "GLFW/glfw3.h"

#include <vector>
#include <memory>
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>

namespace winter {

    enum class KeyEvent {
        KEY_DOWN,
        KEY_UP
    };

    using KeyType = decltype(GLFW_KEY_LAST);
    using KeyEventType = std::underlying_type_t<KeyEvent>;

	struct KeyEventListener {
		virtual ~KeyEventListener() = default;
		virtual void handleKeyEvent(KeyType key) = 0;
	};
	using KeyEventListenerPtr = std::unique_ptr<KeyEventListener>;

	struct MouseListener {
		virtual ~MouseListener() = default;
		virtual void handleMouseEvent(const glm::vec2& mousePos, const glm::vec2& lastMousePos) = 0;
	};
	using MouseListenerPtr = std::unique_ptr<MouseListener>;

    class InputManager final {

    public:

        static InputManager& getInstance();

        InputManager(const InputManager&) = delete;
        InputManager& operator=(const InputManager&) = delete;

		const glm::vec2& getMousePosition() const;

        void tick();
        void hookInto(const Window& window);
        void registerEventListener(KeyEvent event, KeyEventListenerPtr eventListener);
		void registerMouseListener(MouseListenerPtr mouseListener);

    private:

        InputManager() = default;

		glm::vec2 mousePosition;
		glm::vec2 lastMousePosition;
        std::unordered_map<KeyEventType, std::vector<KeyEventListenerPtr>> eventListeners;
        std::unordered_set<KeyType> keysDown;
        std::unordered_set<KeyType> keysUp;
		std::vector<MouseListenerPtr> mouseListeners;

        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseCallback(GLFWwindow* window, double x, double y);

    };

}