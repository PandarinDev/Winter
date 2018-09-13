#include "Graphics/Mesh.h"

namespace winter {

    Mesh::Mesh(GLuint vertexArrayObject, GLuint vertexBufferObject, std::size_t numIndices) :
        vertexArrayObject(vertexArrayObject), vertexBufferObject(vertexBufferObject), numIndices(numIndices) {}

    Mesh::~Mesh() {
        glDeleteVertexArrays(1, &vertexArrayObject);
        glDeleteBuffers(1, &vertexArrayObject);
    }

    GLuint Mesh::getVertexArrayObject() const {
        return vertexArrayObject;
    }

    GLuint Mesh::getVertexBufferObject() const {
        return vertexBufferObject;
    }
    
    std::size_t Mesh::getNumberOfIndices() const {
        return numIndices;
    }

}