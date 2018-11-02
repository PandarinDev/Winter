#include "Graphics/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

namespace winter {

    const glm::vec3 Camera::WORLD_UP(0.0f, 1.0f, 0.0f);

    Camera::Camera(const glm::vec3& position) :
        position(position),
		direction(glm::vec3(0.0f, 0.0f, -1.0f)),
		right(glm::vec3(1.0f, 0.0f, 0.0f)),
        up(WORLD_UP),
        pitch(0.0f), yaw(0.0f) {}

    void Camera::translate(const glm::vec3& translation) {
        position += translation;
    }

    void Camera::rotate(float pitch, float yaw) {
        this->pitch = std::clamp(this->pitch + pitch, -89.0f, 89.0f);
        this->yaw = glm::mod(this->yaw + yaw, 360.0f);
		direction = glm::normalize(glm::vec3(
			cos(glm::radians(this->pitch)) * cos(glm::radians(this->yaw)),
			sin(glm::radians(this->pitch)),
			cos(glm::radians(this->pitch)) * sin(glm::radians(this->yaw))
		));
        right = glm::cross(direction, WORLD_UP);
        up = glm::cross(right, direction);
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

	const glm::vec3& Camera::getUp() const {
        return up;
    }

    glm::mat4 Camera::calculateTransformationMatrix() const {
        return glm::lookAt(position, position + direction, up);
    }

}