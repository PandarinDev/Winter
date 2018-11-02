#pragma once

namespace winter {

    class Scene {

    public:

        virtual ~Scene() = default;
        virtual void tick() = 0;

    };

}