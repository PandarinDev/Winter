#pragma once

#include <vector>
#include <string>

namespace winter {

    class StringUtils final {

    public:

        static std::vector<std::string> split(const std::string& input, char delimiter = ' ');

    private:

        StringUtils() = default;

    };

}