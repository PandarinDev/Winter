#pragma once

#include "Graphics/Mesh.h"

#include <string>
#include <memory>

namespace winter {

    class MeshFactory final {

    public:

        static std::unique_ptr<Mesh> loadFile(MeshFormat format, const std::string& filePath);

    private:

        MeshFactory() = default;

        static std::unique_ptr<Mesh> loadObjFile(const std::string& contents);

    };

}