#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace winter {

    class Camera final {

    public:

        Camera(const glm::vec3& position = { 0.0f, 0.0f, 0.0f });

        void translate(const glm::vec3& translation);

		void setDirection(const glm::vec3& direction);
		void setRight(const glm::vec3& right);

        const glm::vec3& getPosition() const;
        const glm::vec3& getDirection() const;
		const glm::vec3& getRight() const;
		glm::vec3 calculateUp() const;
        glm::mat4 calculateTransformationMatrix() const;

    private:

        glm::vec3 position;
        glm::vec3 direction;
		glm::vec3 right;

    };

}