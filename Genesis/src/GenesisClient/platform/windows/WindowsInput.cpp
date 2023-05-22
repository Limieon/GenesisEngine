#include "WindowsInput.hpp"

#include "GenesisClient/Application.hpp"
#include "GenesisClient/Defines.hpp"

#include <GLFW/glfw3.h>

namespace ge {
	namespace client {
		Input* Input::instance = new WindowsInput();

		bool WindowsInput::isKeyDownImpl(KeyCode keycode) {
			auto window = (GLFWwindow*) Application::getInstance().getWindow().getNativeWindow();
			auto state = glfwGetKey(window, keycode);
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}
		bool WindowsInput::isMouseDownImpl(int32 button) {
			auto window = (GLFWwindow*) Application::getInstance().getWindow().getNativeWindow();
			auto state = glfwGetMouseButton(window, button);
			return state == GLFW_PRESS;
		}
		float32 WindowsInput::getMouseXImpl() {
			auto [x, y] = getMousePosImpl();
			return x;
		}
		float32 WindowsInput::getMouseYImpl() {
			auto [x, y] = getMousePosImpl();
			return y;
		}
		std::pair<float32, float32> WindowsInput::getMousePosImpl() {
			auto window = (GLFWwindow*) Application::getInstance().getWindow().getNativeWindow();
			float64 x, y;
			glfwGetCursorPos(window, &x, &y);
			return {(float32) x, (float32) y};
		}
	}
}
