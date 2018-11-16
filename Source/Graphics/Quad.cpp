#include "Graphics/Quad.h"
#include "Factory/MeshFactory.h"

namespace winter {

    std::unique_ptr<Mesh> Quad::createMesh(float width, float height) {
        std::vector<VertexAttribute> attributes = {
            { 0, 2 }, // Position
            { 1, 2 }  // Texture coordinate
        };
        return MeshFactory::loadGeometry(createGeometry(width, height), attributes);
    }

    Geometry Quad::createGeometry(float width, float height) {
        return {
            0.0f, 0.0f,
            0.0f, 0.0f,
            width, 0.0f,
            1.0f, 0.0f,
            width, height,
            1.0f, 1.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,
            width, height,
            1.0f, 1.0f,
            0.0f, height,
            0.0f, 1.0f
        };
    }

}