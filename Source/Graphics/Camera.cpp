#include "Graphics/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace winter {

    Camera::Camera(const glm::vec3& position, const glm::vec3& direction) :
        position(position), direction(direction) {}

    void Camera::translate(const glm::vec3& translation) {
        position += translation;
    }

	void Camera::setDirection(const glm::vec3& direction) {
		this->direction = direction;
	}

    const glm::vec3& Camera::getPosition() const {
        return position;
    }

    const glm::vec3& Camera::getDirection() const {
        return direction;
    }

    glm::mat4 Camera::calculateTransformationMatrix() const {
        return glm::lookAt(position, position + direction, glm::vec3(0.0f, 1.0f, 0.0f));
    }

}