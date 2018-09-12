#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace winter {

    class Camera final {

    public:

        Camera(const glm::vec3& position = { 0.0f, 0.0f, 0.0f }, const glm::vec3& direction = { 0.0f, 0.0f, -1.0f });

        void translate(const glm::vec3& translation);

        const glm::vec3& getPosition() const;
        const glm::vec3& getDirection() const;
        glm::mat4 calculateTransformationMatrix() const;

    private:

        glm::vec3 position;
        glm::vec3 direction;

    };

}