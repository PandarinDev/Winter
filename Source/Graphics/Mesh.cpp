#include "Graphics/Mesh.h"

#include <glm/gtc/matrix_transform.hpp>

namespace winter {

    Mesh::Mesh(GLuint vertexArrayObject, GLuint vertexBufferObject, std::size_t numIndices) :
        vertexArrayObject(vertexArrayObject), vertexBufferObject(vertexBufferObject),
		numIndices(numIndices), transformations(glm::mat4(1.0f)) {}

    Mesh::~Mesh() {
        glDeleteVertexArrays(1, &vertexArrayObject);
        glDeleteBuffers(1, &vertexArrayObject);
    }

	void Mesh::translate(const glm::vec3& translation) {
		transformations = glm::translate(transformations, translation);
	}

	const glm::mat4& Mesh::getTransformations() const {
		return transformations;
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