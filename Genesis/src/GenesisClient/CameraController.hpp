#pragma once
#include "GenesisClient/renderer/Camera.hpp"

#include <GenesisCore/Timestep.hpp>
#include <GenesisCore/event/KeyEvent.hpp>
#include <GenesisCore/event/MouseEvent.hpp>
#include <GenesisCore/event/WindowEvent.hpp>

namespace ge {
	namespace client {
		class OrthographicCameraController {
		public:
			OrthographicCameraController(float32 aspectRatio, bool rotation = false);

			void onUpdate(ge::core::Timestep ts);
			void onEvent(ge::core::Event& e);

			inline OrthographicCamera& getCamera() { return camera; }
			inline const OrthographicCamera& getCamera() const { return camera; }

		private:
			bool onMouseScrolled(ge::core::MouseScrolledEvent& e);
			bool onWindowResized(ge::core::WindowResizeEvent& e);

		private:
			float32 aspectRatio;
			float32 zoomLevel = 1.f;
			OrthographicCamera camera;

			bool useRotation;

			float32 rotation = 0.f;
			glm::vec3 position = {0.f, 0.f, 0.f};

			float32 translationSpeed = 5.f;
			float32 rotationSpeed = 1.f;
		};

		class PerspectiveCameraController {
		public:
			PerspectiveCameraController(float32 aspectRatio, float32 fov);

			void onUpdate(ge::core::Timestep ts);
			void onEvent(ge::core::Event& e);

			inline PerspectiveCamera& getCamera() { return camera; }
			inline const PerspectiveCamera& getCamera() const { return camera; }

		private:
			bool onMouseMoved(ge::core::MouseMovedEvent& e);
			bool onWindowResize(ge::core::WindowResizeEvent& e);
			bool onKeyDown(ge::core::KeyDownEvent& e);

			void moveUp(float32 amount);
			void moveRight(float32 amount);
			void moveForward(float32 amount);

		private:
			FPSCamera camera;

			float32 translationSpeed = 50.f;
			float32 rotationSpeed = 0.05f;
		};
	}
}
