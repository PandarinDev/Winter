#include "Graphics/Lights/PointLight.h"

namespace winter {

    PointLight::PointLight(const glm::vec3& position, float radius, const glm::vec3& color) :
        position(position), radius(radius), color(color) {}

    const glm::vec3& PointLight::getPosition() const {
        return position;
    }

    float PointLight::getRadius() const {
        return radius;
    }

    const glm::vec3& PointLight::getColor() const {
        return color;
    }

    void PointLight::setPosition(const glm::vec3& position) {
        this->position = position;
    }

    void PointLight::setRadius(float radius) {
        this->radius = radius;
    }

    void PointLight::setColor(const glm::vec3& color) {
        this->color = color;
    }

}