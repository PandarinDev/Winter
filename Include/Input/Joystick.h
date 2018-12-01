#pragma once

#include <GLFW/glfw3.h>

#include <string>
#include <vector>

namespace winter {

    class Joystick final {

    public:

        using Id = decltype(GLFW_JOYSTICK_1);

        Joystick(Id id, const std::string& name);

        Id getId() const;
        const std::string& getName() const;
        std::vector<bool> getButtonStates() const;
        std::vector<float> getAxisStates() const;

    private:

        Id id;
        std::string name;

    };

}