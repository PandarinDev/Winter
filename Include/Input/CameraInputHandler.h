#pragma once

#include "Graphics/Camera.h"
#include "Input/InputManager.h"

namespace winter {

	class CameraKeyInputHandler final : public KeyEventListener {

	public:

		CameraKeyInputHandler(Camera& camera);

		void handleKeyEvent(KeyType key) override;

	private:
		
		static constexpr float CAMERA_SPEED = 0.1f;
		
		Camera& camera;

	};

	class CameraMouseInputHandler final : public MouseEventListener {

	public:

		CameraMouseInputHandler(Camera& camera);

		void handleMouseEvent(const glm::vec2& mousePos, const glm::vec2& lastMousePos) override;

	private:

		static constexpr float MOUSE_SENSITIVITY = 0.2f;

		Camera& camera;

	};

}