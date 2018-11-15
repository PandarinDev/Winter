#include "Scenes/DefaultScene.h"
#include "Factory/MeshFactory.h"
#include "Input/CameraInputHandler.h"

namespace winter {

    static std::unique_ptr<Text> textPtr = nullptr;

    DefaultScene::DefaultScene(Renderer& renderer, InputManager& inputManager) : renderer(renderer) {
        dragonPtr = MeshFactory::loadFile(MeshFormat::OBJ, "Assets/Meshes/DragonWithNormals.obj");
        textPtr = renderer.getFont().generateText("Hello, world!");
		textPtr->getMesh().translate(glm::vec3(100.0f, 300.0f, 0.0f));
        auto& camera = renderer.getCamera();
        inputManager.registerEventListener(KeyEvent::KEY_DOWN, std::make_unique<CameraKeyInputHandler>(camera));
        inputManager.registerMouseListener(std::make_unique<CameraMouseInputHandler>(camera));
    }

    void DefaultScene::tick() {
        renderer.render(*dragonPtr);
        renderer.render(*textPtr);
    }

}