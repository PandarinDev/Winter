#pragma once

#include "Graphics/Mesh.h"
#include "Graphics/OBJ/ObjVertex.h"

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

#include <string>
#include <memory>
#include <array>
#include <vector>

namespace winter {

    class MeshFactory final {

    public:

        static std::unique_ptr<Mesh> loadFile(MeshFormat format, const std::string& filePath);

    private:

        MeshFactory() = default;

        static std::unique_ptr<Mesh> loadObjFile(const std::string& contents);
		static ObjVertex extractObjFace(const std::string& face);
		static std::vector<float> combineObjBuffers(
			const std::vector<glm::vec3>& vertices,
			const std::vector<glm::vec2>& uvs,
			const std::vector<glm::vec3>& normals,
			const std::vector<ObjVertex>& indices);

    };

}