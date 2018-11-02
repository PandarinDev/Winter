#pragma once

// Important: GLAD must be included before GLFW
#include "External/glad.h"
#include <GLFW/glfw3.h>

#include "Configuration.h"
#include "Window.h"
#include "Input/InputManager.h"
#include "Graphics/Renderer.h"
#include "Scene.h"

#include <memory>

namespace winter {

    class Engine final {

    public:

        static Engine& getInstance();

        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        void init(const Configuration& config);
        void start();

        Window& getWindow() const;
        InputManager& getInputManager() const;
        Renderer& getRenderer() const;
        Scene& getScene() const;

        void setScene(std::unique_ptr<Scene> scene);

    private:

        Engine() = default;

        std::unique_ptr<Window> window;
        std::unique_ptr<InputManager> inputManager;
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Scene> scene;

        void initGLFW();
        void initGLAD();

    };

}