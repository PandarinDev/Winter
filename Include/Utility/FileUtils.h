#pragma once

#include <string>

namespace winter {

    class FileUtils final {

    public:

        static std::string readFileContents(const std::string& filePath);

    private:

        FileUtils() = default;

    };

}