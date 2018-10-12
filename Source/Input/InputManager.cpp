#include "Input/InputManager.h"
#include "Utility/TypeUtils.h"

#include <algorithm>

namespace winter {

    InputManager& InputManager::getInstance() {
        static InputManager instance;
        return instance;
    }

	const glm::vec2& InputManager::getMousePosition() const {
		return mousePosition;
	}

    void InputManager::tick() {
		static const auto keyDownValue = TypeUtils::enumValue(KeyEvent::KEY_DOWN);
        static const auto keyUpValue = TypeUtils::enumValue(KeyEvent::KEY_UP);
        // Handle keyboard events
		auto downListeners = eventListeners.find(keyDownValue);
        auto upListeners = eventListeners.find(keyUpValue);
        if (downListeners != eventListeners.end()) {
            for (auto key : keysDown) {
                for (const auto& listener : downListeners->second) {
                    listener->handleKeyEvent(key);
                }
            }
        }
        if (upListeners != eventListeners.end()) {
            for (auto key : keysUp) {
                for (const auto& listener : upListeners->second) {
                    listener->handleKeyEvent(key);
                }
            }
        }
        keysUp.clear();

		// Handle mouse events
		for (const auto& listener : mouseListeners) {
			listener->handleMouseEvent(mousePosition, lastMousePosition);
		}
		lastMousePosition = mousePosition;
    }

    void InputManager::hookInto(const Window& window) {
        window.setKeyCallback(keyCallback);
		window.setMouseCallback(mouseCallback);
    }

    void InputManager::registerEventListener(KeyEvent event, KeyEventListenerPtr eventListener) {
        auto eventValue = TypeUtils::enumValue(event);
        auto it = eventListeners.find(eventValue);
        if (it == eventListeners.end()) {
            it = eventListeners.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(eventValue),
                std::forward_as_tuple()).first;
        }
        it->second.emplace_back(std::move(eventListener));
    }

	void InputManager::registerMouseListener(MouseListenerPtr mouseListener) {
		mouseListeners.emplace_back(std::move(mouseListener));
	}

    void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto& instance = getInstance();
        switch (action) {
        case GLFW_PRESS:
            instance.keysDown.emplace(key);
            break;
        case GLFW_RELEASE:
            instance.keysDown.erase(key);
            instance.keysUp.emplace(key);
            break;
        }
    }

	void InputManager::mouseCallback(GLFWwindow* window, double x, double y) {
		auto& instance = getInstance();
		instance.lastMousePosition = instance.mousePosition;
		instance.mousePosition.x = static_cast<float>(x);
		instance.mousePosition.y = static_cast<float>(y);
	}

}