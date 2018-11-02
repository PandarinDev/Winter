#include "Timer.h"

#include <GLFW/glfw3.h>

namespace winter {

    Timer::Timer() : frames(0), fps(0), delta(0.0f) {
        float time = getTime();
        lastFrame = time;
        lastFps = time;
    }

    void Timer::tick() {
        float time = getTime();
        if (time - lastFps >= 1.0f) {
            fps = frames;
            frames = 0;
            lastFps = time;
        }
        ++frames;
        delta = time - lastFrame;
        lastFrame = time;
    }

    float Timer::getTime() const {
        return static_cast<float>(glfwGetTime());
    }

    int Timer::getFPS() const {
        return fps;
    }

    float Timer::getDelta() const {
        return delta;
    }

}