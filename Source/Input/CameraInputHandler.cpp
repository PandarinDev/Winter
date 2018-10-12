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
		glm::vec2 mouseDelta = mousePos - lastMousePos;
		// Calculate new right vector
		glm::vec3 cameraRight = camera.getRight();
		cameraRight = glm::rotateY(cameraRight, -glm::radians(mouseDelta.x) * MOUSE_SENSITIVITY);
		camera.setRight(cameraRight);
		// Calculate new direction vector
		glm::vec3 cameraDir = camera.getDirection();
		cameraDir = glm::rotate(cameraDir, -glm::radians(mouseDelta.y) * MOUSE_SENSITIVITY, cameraRight);
		cameraDir = glm::rotateY(cameraDir, -glm::radians(mouseDelta.x) * MOUSE_SENSITIVITY);
		camera.setDirection(cameraDir);
	}

}