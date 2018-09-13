#pragma once

#include "Window.h"

#include "GLFW/glfw3.h"

#include <vector>
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
    using KeyEventListener = std::function<void(KeyType)>;

    class InputManager final {

    public:

        static InputManager& getInstance();

        InputManager(const InputManager&) = delete;
        InputManager& operator=(const InputManager&) = delete;

        void tick();
        void hookInto(const Window& window);
        void registerEventListener(KeyEvent event, const KeyEventListener& eventListener);

    private:

        InputManager() = default;

        std::unordered_map<KeyEventType, std::vector<KeyEventListener>> eventListeners;
        std::unordered_set<KeyType> keysDown;
        std::unordered_set<KeyType> keysUp;

        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    };

}