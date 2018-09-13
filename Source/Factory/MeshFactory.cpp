#include "Factory/MeshFactory.h"
#include "Utility/FileUtils.h"
#include "Utility/StringUtils.h"

#include "glm/vec3.hpp"

#include <vector>
#include <sstream>
#include <stdexcept>

namespace winter {

    std::unique_ptr<Mesh> MeshFactory::loadFile(MeshFormat format, const std::string& filePath) {
        switch (format) {
        case MeshFormat::OBJ:
            return loadObjFile(filePath);
        default:
            throw std::runtime_error("Unsupported format.");
        }
    }

    std::unique_ptr<Mesh> MeshFactory::loadObjFile(const std::string& filePath) {
        std::vector<float> vertices;
        std::vector<unsigned> indices;
        std::stringstream fileStream(FileUtils::readFileContents(filePath));
        int lineCounter = 1;
        for (std::string line; std::getline(fileStream, line); ++lineCounter) {
            // Skip empty lines
            if (line.empty()) {
                continue;
            }
            std::stringstream lineStream(line);
            std::string type;
            lineStream >> type;
            // Vertex entry
            if (type == "v") {
                float x, y, z;
                lineStream >> x >> y >> z;
                vertices.emplace_back(x);
                vertices.emplace_back(y);
                vertices.emplace_back(z);
            }
            // Face entry
            else if (type == "f") {
                unsigned v1, v2, v3;
                lineStream >> v1 >> v2 >> v3;
                indices.emplace_back(v1 - 1);
                indices.emplace_back(v2 - 1);
                indices.emplace_back(v3 - 1);
            }
        }
        // Upload data to the GPU
        GLuint vertexArrayObject, vertexBufferObject;
        glCreateVertexArrays(1, &vertexArrayObject);
        glCreateBuffers(1, &vertexBufferObject);
        glNamedBufferStorage(
            vertexBufferObject,
            indices.size() * sizeof(unsigned) + vertices.size() * sizeof(float),
            nullptr, GL_DYNAMIC_STORAGE_BIT);
        glNamedBufferSubData(vertexBufferObject, 0, indices.size() * sizeof(unsigned), indices.data());
        glNamedBufferSubData(vertexBufferObject, indices.size() * sizeof(unsigned), vertices.size() * sizeof(float), vertices.data());
        glEnableVertexArrayAttrib(vertexArrayObject, 0);
        glVertexArrayVertexBuffer(vertexArrayObject, 0, vertexBufferObject, indices.size() * sizeof(unsigned), 3 * sizeof(float));
        glVertexArrayAttribFormat(vertexArrayObject, 0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vertexArrayObject, 0, 0);
        glVertexArrayElementBuffer(vertexArrayObject, vertexBufferObject);
        // Create the mesh
        return std::make_unique<Mesh>(vertexArrayObject, vertexBufferObject, indices.size());
    }

}