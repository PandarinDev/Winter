#pragma once

#include "External/glad.h"

#include <glm/mat4x4.hpp>

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

		void translate(const glm::vec3& translation);

		const glm::mat4& getTransformations() const;
        GLuint getVertexArrayObject() const;
        GLuint getVertexBufferObject() const;
        std::size_t getNumberOfIndices() const;

    private:

		glm::mat4 transformations;
        const GLuint vertexArrayObject;
        const GLuint vertexBufferObject;
        const std::size_t numIndices;

    };

}