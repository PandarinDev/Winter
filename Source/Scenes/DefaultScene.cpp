#include "Scenes/DefaultScene.h"
#include "Factory/MeshFactory.h"
#include "Input/CameraInputHandler.h"

namespace winter {

    DefaultScene::DefaultScene(Renderer& renderer, InputManager& inputManager) : renderer(renderer) {
        dragonPtr = MeshFactory::loadFile(MeshFormat::OBJ, "Assets/Meshes/DragonWithNormals.obj");
        textPtr = std::shared_ptr<Text>(renderer.getFont().generateText("Hello, world!").release());
		textPtr->getMesh().translate(glm::vec3(100.0f, 300.0f, 0.0f));
        auto& camera = renderer.getCamera();
        inputManager.registerKeyEventListener(KeyEvent::KEY_DOWN, std::make_unique<CameraKeyInputHandler>(camera));
        inputManager.registerMouseEventListener(std::make_unique<CameraMouseInputHandler>(camera));
    }

    void DefaultScene::tick() {
        renderer.render(*dragonPtr);
        renderer.render(textPtr);
    }

}