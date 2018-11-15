#pragma once

#include "Graphics/Font.h"

#include <string>
#include <memory>

namespace winter {

    class FontFactory final {

    public:

        static std::unique_ptr<Font> createFromFile(const std::string& filePath);

    private:

        FontFactory() = default;

    };

}