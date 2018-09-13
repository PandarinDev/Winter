#include "Utility/FileUtils.h"

#include <fstream>
#include <stdexcept>

namespace winter {

    std::string FileUtils::readFileContents(const std::string& filePath) {
        std::ifstream fileHandle(filePath);
        if (!fileHandle) {
            throw std::runtime_error("Failed to open file at '" + filePath + "'.");
        }
        std::string contents;
        for (std::string line; std::getline(fileHandle, line);) {
            contents += line + '\n';
        }
        return contents;
    }

}