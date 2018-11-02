#include "Input/CameraInputHandler.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/rotate_vector.hpp"

#include <iostream>

namespace winter {

	constexpr float CameraKeyInputHandler::CAMERA_SPEED;
	constexpr float CameraMouseInputHandler::MOUSE_SENSITIVITY;

	CameraKeyInputHandler::CameraKeyInputHandler(Camera& camera) : camera(camera) {}

	void CameraKeyInputHandler::handleKeyEvent(KeyType key) {
		glm::vec3 translation(0.0f, 0.0f, 0.0f);
		switch (key) {
		case GLFW_KEY_A:
			translation = -camera.getRight();
			break;
		case GLFW_KEY_D:
			translation = camera.getRight();
			break;
		case GLFW_KEY_W:
			translation = camera.getDirection();
			break;
		case GLFW_KEY_S:
			translation = -camera.getDirection();
			break;
		case GLFW_KEY_Q:
			translation = glm::vec3(0.0f, -1.0f, 0.0f);
			break;
		case GLFW_KEY_E:
			translation = glm::vec3(0.0f, 1.0f, 0.0f);
			break;
		}
		camera.translate(translation * CAMERA_SPEED);
	}

	CameraMouseInputHandler::CameraMouseInputHandler(Camera& camera) : camera(camera) {}

	void CameraMouseInputHandler::handleMouseEvent(const glm::vec2& mousePos, const glm::vec2& lastMousePos) {
		glm::vec2 mouseDelta = (mousePos - lastMousePos) * MOUSE_SENSITIVITY;
		camera.rotate(-mouseDelta.y, mouseDelta.x);
	}

}