#pragma once

#include "External/glad.h"
#include "Window.h"
#include "Input/Joystick.h"

#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>

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

	struct MouseEventListener {
		virtual ~MouseEventListener() = default;
		virtual void handleMouseEvent(const glm::vec2& mousePos, const glm::vec2& lastMousePos) = 0;
	};

    enum class JoystickButtonEvent {
        BUTTON_PRESS, BUTTON_RELEASE
    };

    struct JoystickEventListener {
        virtual ~JoystickEventListener() = default;
        virtual void handleButtonEvent(Joystick::Id id, JoystickButtonEvent event, int button) = 0;
        virtual void handleAxisEvent(Joystick::Id id, float value, int axis) = 0;
    };

    class InputManager final {

    public:
        
        InputManager();

        const glm::vec2& getMousePosition() const;

        void tick();
        void hookInto(const Window& window);
        void registerKeyEventListener(KeyEvent event, std::unique_ptr<KeyEventListener> eventListener);
		void registerMouseEventListener(std::unique_ptr<MouseEventListener> eventListener);
        void registerJoystickEventListener(std::unique_ptr<JoystickEventListener> eventListener);

    private:

        bool mouseCoordinated;
		glm::vec2 mousePosition;
		glm::vec2 lastMousePosition;
        std::unordered_map<Joystick::Id, std::unique_ptr<Joystick>> joysticks;
        std::unordered_map<KeyEventType, std::vector<std::unique_ptr<KeyEventListener>>> eventListeners;
        std::unordered_set<KeyType> keysDown;
        std::unordered_set<KeyType> keysUp;
		std::vector<std::unique_ptr<MouseEventListener>> mouseListeners;
        std::vector<std::unique_ptr<JoystickEventListener>> joystickListeners;

        void discoverJoysticks();

        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseCallback(GLFWwindow* window, double x, double y);
        static void joystickCallback(int joy, int event);

    };

}