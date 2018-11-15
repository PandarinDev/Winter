#pragma once

#include <cstdint>

namespace winter {

    class FontChar final {

    public:

        using Id = unsigned int;

        Id id;
        unsigned short x;
        unsigned short y;
        unsigned short width;
        unsigned short height;
        short xOffset;
        short yOffset;
        short xAdvance;

        FontChar(
                unsigned int id,
                unsigned short x,
                unsigned short y,
                unsigned short width,
                unsigned short height,
                short xOffset,
                short yOffset,
                short xAdvance) :
                id(id), x(x), y(y), width(width), height(height),
                xOffset(xOffset), yOffset(yOffset), xAdvance(xAdvance) {}

    };

}