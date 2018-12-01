#include "Input/Joystick.h"

namespace winter {

    Joystick::Joystick(Id id, const std::string& name) :
        id(id), name(name) {}

    Joystick::Id Joystick::getId() const {
        return id;
    }

    const std::string& Joystick::getName() const {
        return name;
    }

    std::vector<bool> Joystick::getButtonStates() const {
        int count;
        const unsigned char* buttons = glfwGetJoystickButtons(id, &count);
        std::vector<bool> buttonStates(count);
        for (int i = 0; i < count; ++i) {
            buttonStates[i] = (buttons[i] == GLFW_PRESS);
        }
        return buttonStates;
    }

    std::vector<float> Joystick::getAxisStates() const {
        int count;
        const float* axes = glfwGetJoystickAxes(id, &count);
        std::vector<float> axisStates(count);
        for (int i = 0; i < count; ++i) {
            axisStates[i] = axes[i];
        }
        return axisStates;
    }

}