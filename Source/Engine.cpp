#include "Engine.h"

#include "Factory/ShaderProgramFactory.h"
#include "Factory/FontFactory.h"
#include "Scenes/DefaultScene.h"

#include <glm/glm.hpp>

namespace winter {

    Engine& Engine::getInstance() {
        static Engine instance;
        return instance;
    }

    void Engine::init(const Configuration& config) {
        initGLFW();
        window = std::make_unique<Window>(
            config.windowTitle,
            config.windowWidth,
            config.windowHeight,
            config.windowVSync,
            config.windowFullScreen);
        window->captureCursor();
        inputManager = std::make_unique<InputManager>();
        inputManager->hookInto(*window);
        initGLAD();
        renderer = std::make_unique<Renderer>(
            glm::vec3(0.1f, 0.5f, 0.95f),
            ShaderProgramFactory::createDefault2DProgram(),
		    ShaderProgramFactory::createDefault3DProgram(),
            FontFactory::createFromFile("Assets/Fonts/Roboto/roboto.fnt"),
		    glm::radians(config.rendererFieldOfView),
		    config.windowWidth,
            config.windowHeight,
            config.rendererDrawClose,
            config.rendererDrawDistance);
        scene = std::make_unique<DefaultScene>(getRenderer(), getInputManager());
    }

    void Engine::start() {
        while (!window->shouldClose()) {
            window->pollEvents();
            inputManager->tick();
            // Render and swap buffers
            renderer->clearBuffers();
            scene->tick();
            window->swapBuffers();
        }
    }

    Window& Engine::getWindow() const {
        return *window;
    }

    InputManager& Engine::getInputManager() const {
        return *inputManager;
    }

    Renderer& Engine::getRenderer() const {
        return *renderer;
    }

    Scene& Engine::getScene() const {
        return *scene;
    }

    void Engine::setScene(std::unique_ptr<Scene> scene) {
        this->scene = std::move(scene);
    }

    void Engine::initGLFW() {
        if (!glfwInit()) {
		    throw std::runtime_error("Failed to initialize GLFW.");
	    }
    }

    void Engine::initGLAD() {
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    }

}