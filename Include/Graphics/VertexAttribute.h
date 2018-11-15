#pragma once

namespace winter {

    class VertexAttribute final {

    public:

        unsigned index;
        unsigned components;

        VertexAttribute(unsigned index, unsigned components) :
            index(index), components(components) {}

    };

}