#include "Utility/StringUtils.h"

#include <sstream>

namespace winter {

    std::vector<std::string> StringUtils::split(const std::string& input, char delimiter) {
        std::stringstream inputStream(input);
        std::vector<std::string> result;
        for (std::string match; std::getline(inputStream, match, delimiter);) {
            result.emplace_back(std::move(match));
        }
        return result;
    }

}