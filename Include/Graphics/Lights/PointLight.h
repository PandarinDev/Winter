#pragma once

#include <glm/vec3.hpp>

namespace winter {

    class PointLight final {

    public:

        PointLight(const glm::vec3& position, float radius, const glm::vec3& color);

        const glm::vec3& getPosition() const;
        float getRadius() const;
        const glm::vec3& getColor() const;

        void setPosition(const glm::vec3& position);
        void setRadius(float radius);
        void setColor(const glm::vec3& color);

    private:

        glm::vec3 position;
        float radius;
        glm::vec3 color;

    };

}