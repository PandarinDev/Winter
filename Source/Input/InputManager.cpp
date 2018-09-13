#include "Input/InputManager.h"
#include "Utility/TypeUtils.h"

#include <algorithm>

namespace winter {

    InputManager& InputManager::getInstance() {
        static InputManager instance;
        return instance;
    }

    void InputManager::tick() {
        static const auto keyDownValue = TypeUtils::enumValue(KeyEvent::KEY_DOWN);
        static const auto keyUpValue = TypeUtils::enumValue(KeyEvent::KEY_UP);
        auto downListeners = eventListeners.find(keyDownValue);
        auto upListeners = eventListeners.find(keyUpValue);
        if (downListeners != eventListeners.end()) {
            for (auto key : keysDown) {
                for (const auto& listener : downListeners->second) {
                    listener(key);
                }
            }
        }
        if (upListeners != eventListeners.end()) {
            for (auto key : keysUp) {
                for (const auto& listener : upListeners->second) {
                    listener(key);
                }
            }
        }
        keysUp.clear();
    }

    void InputManager::hookInto(const Window& window) {
        window.setKeyCallback(keyCallback);
    }

    void InputManager::registerEventListener(KeyEvent event, const KeyEventListener& eventListener) {
        auto eventValue = TypeUtils::enumValue(event);
        auto it = eventListeners.find(eventValue);
        if (it == eventListeners.end()) {
            it = eventListeners.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(eventValue),
                std::forward_as_tuple()).first;
        }
        it->second.emplace_back(eventListener);
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

}