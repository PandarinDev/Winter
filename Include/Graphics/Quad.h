#pragma once

#include "Graphics/Mesh.h"
#include "Graphics/Geometry.h"

#include <memory>

namespace winter {

    class Quad final {

    public:

        static std::unique_ptr<Mesh> createMesh(float width, float height);
        static Geometry createGeometry(float width, float height);

    private:

        Quad() = default;

    };

}