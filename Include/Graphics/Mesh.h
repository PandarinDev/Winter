#pragma once

#include "External/glad.h"

#include <cstddef>

namespace winter {

    enum class MeshFormat {
        OBJ
    };

    class Mesh final {

    public:

        Mesh(GLuint vertexArrayObject, GLuint vertexBufferObject, const std::size_t numIndices);
        ~Mesh();
        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        GLuint getVertexArrayObject() const;
        GLuint getVertexBufferObject() const;
        std::size_t getNumberOfIndices() const;

    private:

        const GLuint vertexArrayObject;
        const GLuint vertexBufferObject;
        const std::size_t numIndices;

    };

}