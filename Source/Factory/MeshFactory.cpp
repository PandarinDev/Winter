#include "Factory/MeshFactory.h"
#include "Utility/FileUtils.h"
#include "Utility/StringUtils.h"

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
        std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals;
        std::vector<ObjVertex> indices;
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
				vertices.emplace_back(x, y, z);
            }
			// Texture coordinates
			else if (type == "vt") {
				float x, y;
				lineStream >> x >> y;
				uvs.emplace_back(x, y);
			}
			// Vertex normal
			else if (type == "vn") {
				float x, y, z;
				lineStream >> x >> y >> z;
				normals.emplace_back(x, y, z);
			}
            // Face entry
            else if (type == "f") {
                std::string f1, f2, f3;
                lineStream >> f1>> f2 >> f3;
                indices.emplace_back(extractObjFace(f1));
                indices.emplace_back(extractObjFace(f2));
                indices.emplace_back(extractObjFace(f3));
            }
        }
		// Combine the buffers
		auto combinedBuffer = combineObjBuffers(vertices, uvs, normals, indices);
        // Upload data to the GPU
        GLuint vertexArrayObject, vertexBufferObject;
        glCreateVertexArrays(1, &vertexArrayObject);
        glCreateBuffers(1, &vertexBufferObject);
		glNamedBufferData(vertexBufferObject, combinedBuffer.size() * sizeof(float), combinedBuffer.data(), GL_STATIC_DRAW);
		glVertexArrayVertexBuffer(vertexArrayObject, 0, vertexBufferObject, 0, 8 * sizeof(float));
		// Enable and describe vertex array attributes
        glEnableVertexArrayAttrib(vertexArrayObject, 0);
		glEnableVertexArrayAttrib(vertexArrayObject, 1);
		glEnableVertexArrayAttrib(vertexArrayObject, 2);
        glVertexArrayAttribFormat(vertexArrayObject, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribFormat(vertexArrayObject, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
		glVertexArrayAttribFormat(vertexArrayObject, 2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float));
        glVertexArrayAttribBinding(vertexArrayObject, 0, 0);
		glVertexArrayAttribBinding(vertexArrayObject, 1, 0);
		glVertexArrayAttribBinding(vertexArrayObject, 2, 0);
        // Create the mesh
        return std::make_unique<Mesh>(vertexArrayObject, vertexBufferObject, indices.size());
    }

	ObjVertex MeshFactory::extractObjFace(const std::string& face) {
		auto entries = StringUtils::split(face, '/');
		std::size_t indices[3];
		for (int i = 0; i < 3; ++i) {
			if (i >= entries.size() || entries[i].empty()) {
				indices[i] = -1u;
				continue;
			}
			indices[i] = std::stoull(entries[i]) - 1;
		}
		return { indices[0], indices[1], indices[2] };
	}

	std::vector<float> MeshFactory::combineObjBuffers(
		const std::vector<glm::vec3>& vertices,
		const std::vector<glm::vec2>& uvs,
		const std::vector<glm::vec3>& normals,
		const std::vector<ObjVertex>& indices) {
		static constexpr std::size_t floatsPerIndex = 8;
		static const glm::vec2 emptyUV(0.0f, 0.0f);
		static const glm::vec3 emptyNormal(0.0f, 0.0f, 0.0f);

		std::vector<float> buffer(indices.size() * floatsPerIndex);
		std::size_t counter = 0;
		for (const auto& index : indices) {
			// Vertex coordinate
			const auto& vertex = vertices.at(index.vertex);
			buffer[counter++] = vertex.x;
			buffer[counter++] = vertex.y;
			buffer[counter++] = vertex.z;
			// UV coordinate (if exists)
			const auto& uv = (index.uv != -1u) ? uvs.at(index.uv) : emptyUV;
			buffer[counter++] = uv.x;
			buffer[counter++] = uv.y;
			// Normal coordinate (if exists)
			const auto& normal = (index.normal != -1u) ? normals.at(index.normal) : emptyNormal;
			buffer[counter++] = normal.x;
			buffer[counter++] = normal.y;
			buffer[counter++] = normal.z;
		}
		return buffer;
	}

}