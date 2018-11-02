#pragma once

#include <string>

namespace winter {

    struct Configuration final {
        // Window configuration
        std::string windowTitle;
        int windowWidth;
        int windowHeight;
        bool windowVSync;
        bool windowFullScreen;
        // Renderer configuration
        float rendererFieldOfView;
        float rendererDrawClose;
        float rendererDrawDistance;
    };

}