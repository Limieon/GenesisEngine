#pragma once
#include "GenesisClient/Defines.hpp"

#include <glm/glm.hpp>

namespace ge {
	namespace client {
		class OrthographicCamera {
		public:
			OrthographicCamera(float32 left, float32 right, float32 bottom, float32 top);
			void setProjection(float32 left, float32 right, float32 bottom, float32 top);

			void setPosition(const glm::vec3& position) {
				this->position = position;
				update();
			}
			void setRotation(const float32 rotation) {
				this->rotation = rotation;
				update();
			}

			inline const glm::vec3& getPosition() const { return position; }
			inline float32 getRotation() const { return rotation; }

			inline const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
			inline const glm::mat4& getViewMatrix() const { return viewMatrix; }
			inline const glm::mat4& getViewProjectionMatrix() const { return viewProjectionMatrix; }

		private:
			void update();

		private:
			glm::mat4 projectionMatrix;
			glm::mat4 viewMatrix;
			glm::mat4 viewProjectionMatrix;

			glm::vec3 position;
			float32 rotation = 0.f;
		};

		/// A free cam, useful for debugging
		class PerspectiveCamera {
		public:
			PerspectiveCamera(float32 aspectRatio, float32 fov);
			void setPerspective(float32 aspectRatio, float32 fov);

			/**
			 * @brief Updates the cameras matrices
			 */
			void update();
			/**
			 * @brief Updates the forward vector using the current yaw and pitch values (Must be called before update())
			 */
			virtual void updateRotation();

			void setPos(const glm::vec3& pos) { this->pos = pos; }
			const glm::vec3& getPos() const { return pos; }
			glm::vec3& getPos() { return pos; }

			const glm::vec3& getRight() const { return right; }
			glm::vec3& getRight() { return right; }

			const glm::vec3& getLookAt() const { return lookAt; }
			glm::vec3& getLookAt() { return lookAt; }

			void setYaw(float32 yaw) { this->yaw = yaw; }
			const float32 getYaw() const { return yaw; }

			void setPitch(float32 pitch) { this->pitch = pitch; }
			const float32 getPitch() const { return pitch; }

			const float32 getAspectRatio() const { return aspectRatio; }
			const float32 getFov() const { return fov; }

			const glm::mat4& getViewProjectionMatrix() const { return viewProjectionMatrix; }
			glm::mat4& getViewProjectionMatrix() { return viewProjectionMatrix; }

		protected:
			float32 aspectRatio, fov;

			glm::mat4 projectionMatrix;
			glm::mat4 viewMatrix;
			glm::mat4 viewProjectionMatrix;

			glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f);
			float32 yaw = 0.f, pitch = 0.f;

			glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
			glm::vec3 lookAt;
			glm::vec3 right;
		};

		/// A FPS Camera (useful in games)
		class FPSCamera: public PerspectiveCamera {
		public:
			FPSCamera(float32 aspectRatio, float32 fov): PerspectiveCamera(aspectRatio, fov) {}

			const glm::vec3& getForward() const { return forward; }
			glm::vec3& getForawrd() { return forward; }

			void updateRotation() override;

		private:
			glm::vec3 forward;
		};
	}
}
