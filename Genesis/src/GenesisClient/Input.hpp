#pragma once
#include "GenesisClient/Defines.hpp"

#include <GenesisCore/KeyCode.hpp>

namespace ge {
	namespace client {
		class Input {
		public:
			inline static bool isKeyDown(KeyCode keycode) { return instance->isKeyDownImpl(keycode); }
			inline static bool isMouseButtonDown(int button) { return instance->isMouseDownImpl(button); }
			inline static float32 getMouseX() { return instance->getMouseXImpl(); }
			inline static float32 getMouseY() { return instance->getMouseYImpl(); }
			inline static std::pair<float32, float32> getMousePos() { return instance->getMousePosImpl(); }

		protected:
			virtual bool isKeyDownImpl(KeyCode keycode) = 0;
			virtual bool isMouseDownImpl(int32 button) = 0;
			virtual float32 getMouseXImpl() = 0;
			virtual float32 getMouseYImpl() = 0;
			virtual std::pair<float32, float32> getMousePosImpl() = 0;

		private:
			static Input* instance;
		};
	}
}
