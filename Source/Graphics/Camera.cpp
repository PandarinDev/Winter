#include "Graphics/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace winter {

    Camera::Camera(const glm::vec3& position) :
        position(position),
		direction(glm::vec3(0.0f, 0.0f, -1.0f)),
		right(glm::vec3(1.0f, 0.0f, 0.0f)) {}

    void Camera::translate(const glm::vec3& translation) {
        position += translation;
    }

	void Camera::setDirection(const glm::vec3& direction) {
		this->direction = direction;
	}

	void Camera::setRight(const glm::vec3& right) {
		this->right = right;
	}

    const glm::vec3& Camera::getPosition() const {
        return position;
    }

    const glm::vec3& Camera::getDirection() const {
        return direction;
    }

	const glm::vec3& Camera::getRight() const {
		return right;
	}

	glm::vec3 Camera::calculateUp() const {
		return glm::cross(right, direction);
	}

    glm::mat4 Camera::calculateTransformationMatrix() const {
        return glm::lookAt(position, position + direction, calculateUp());
    }

}