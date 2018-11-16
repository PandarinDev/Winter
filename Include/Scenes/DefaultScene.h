#pragma once

#include "Scene.h"
#include "Graphics/Renderer.h"
#include "Input/InputManager.h"

#include <memory>

namespace winter {

    class DefaultScene final : public Scene {

    public:

        DefaultScene(Renderer& renderer, InputManager& inputManager);

        void tick() override;

    private:

        Renderer& renderer;
        std::unique_ptr<Mesh> dragonPtr;
        std::shared_ptr<Text> textPtr;

    };

}