#include "CameraController.hpp"

#include "GenesisClient/Application.hpp"
#include "GenesisClient/Input.hpp"

namespace ge {
	namespace client {
		/**********************************
		 * Orthographic Camera Controller *
		 **********************************/
		OrthographicCameraController::OrthographicCameraController(float32 aspectRatio, bool rotation)
		    : aspectRatio(aspectRatio), camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel), useRotation(rotation) {}

		void OrthographicCameraController::onUpdate(ge::core::Timestep ts) {
			if(Input::isKeyDown(Key::A)) {
				position.x -= translationSpeed * ts;
			} else if(Input::isKeyDown(Key::D)) {
				position.x += translationSpeed * ts;
			}

			if(Input::isKeyDown(Key::W)) {
				position.y += translationSpeed * ts;
			} else if(Input::isKeyDown(Key::S)) {
				position.y -= translationSpeed * ts;
			}

			if(useRotation) {
				if(Input::isKeyDown(Key::Q)) {
					rotation += rotationSpeed * ts;
				} else if(Input::isKeyDown(Key::E)) {
					rotation -= rotationSpeed * ts;
				}
				camera.setRotation(rotation);
			}

			camera.setPosition(position);
			translationSpeed = zoomLevel * 2.f;
		}

		void OrthographicCameraController::onEvent(ge::core::Event& e) {
			ge::core::EventDispatcher dispatcher(e);
			dispatcher.dispatch<ge::core::MouseScrolledEvent>(GE_BindEventFunction(OrthographicCameraController::onMouseScrolled));
			dispatcher.dispatch<ge::core::WindowResizeEvent>(GE_BindEventFunction(OrthographicCameraController::onWindowResized));
		}

		bool OrthographicCameraController::onMouseScrolled(ge::core::MouseScrolledEvent& e) {
			zoomLevel -= e.getY() * 0.25f;
			zoomLevel = GE_Max(zoomLevel, 0.25f);
			camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);

			return false;
		}
		bool OrthographicCameraController::onWindowResized(ge::core::WindowResizeEvent& e) {
			aspectRatio = (float32) e.getWidth() / (float32) e.getHeight();
			camera.setProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);

			return false;
		}

		/*********************************
		 * Perspective Camera Controller *
		 *********************************/
		PerspectiveCameraController::PerspectiveCameraController(float32 aspectRatio, float32 fov): camera(aspectRatio, fov) {}

		void PerspectiveCameraController::onUpdate(ge::core::Timestep ts) {
			if(Input::isKeyDown(Key::W)) {
				moveForward(ts * translationSpeed);
			} else if(Input::isKeyDown(Key::S)) {
				moveForward(ts * -translationSpeed);
			}

			if(Input::isKeyDown(Key::A)) {
				moveRight(ts * -translationSpeed);
			} else if(Input::isKeyDown(Key::D)) {
				moveRight(ts * translationSpeed);
			}

			if(Input::isKeyDown(Key::Space)) {
				moveUp(ts * translationSpeed);
			} else if(Input::isKeyDown(Key::LeftShift)) {
				moveUp(ts * -translationSpeed);
			}

			camera.update();
		}
		void PerspectiveCameraController::onEvent(ge::core::Event& e) {
			ge::core::EventDispatcher dispatcher(e);
			dispatcher.dispatch<ge::core::WindowResizeEvent>(GE_BindEventFunction(PerspectiveCameraController::onWindowResize));
			dispatcher.dispatch<ge::core::MouseMovedEvent>(GE_BindEventFunction(PerspectiveCameraController::onMouseMoved));
			dispatcher.dispatch<ge::core::KeyDownEvent>(GE_BindEventFunction(PerspectiveCameraController::onKeyDown));
		}
		bool PerspectiveCameraController::onMouseMoved(ge::core::MouseMovedEvent& e) {
			if(Application::getInstance().getWindow().isCursorGrabbed()) {
				float32 xRel = e.getXRel();
				float32 yRel = e.getYRel();

				camera.setYaw(camera.getYaw() + e.getXRel() * rotationSpeed);
				camera.setPitch(camera.getPitch() - e.getYRel() * rotationSpeed);
				camera.updateRotation();
			}

			return false;
		}
		bool PerspectiveCameraController::onWindowResize(ge::core::WindowResizeEvent& e) {
			camera.setPerspective((float32) e.getWidth() / (float32) e.getHeight(), camera.getFov());

			return false;
		}
		bool PerspectiveCameraController::onKeyDown(ge::core::KeyDownEvent& e) {
			if(e.getKeyCode() == Key::Escape) {
				Application::getInstance().getWindow().setCursorGrabbed(!Application::getInstance().getWindow().isCursorGrabbed());
			}

			return false;
		}

		void PerspectiveCameraController::moveUp(float32 amount) { camera.getPos().y += amount; }
		void PerspectiveCameraController::moveRight(float32 amount) { camera.getPos() += camera.getRight() * amount; }
		void PerspectiveCameraController::moveForward(float32 amount) { camera.getPos() += camera.getForward() * amount; }
	}
}
