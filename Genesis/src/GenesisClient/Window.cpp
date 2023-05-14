#include "Window.hpp"

#include <GenesisCore/Logger.hpp>

namespace ge {
	namespace client {
		Window::Window(const WindowConfiguration& spec) {
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_DECORATED, true);
			glfwWindowHint(GLFW_DOUBLEBUFFER, true);
			glfwWindowHint(GLFW_ALPHA_BITS, 8);
			glfwWindowHint(GLFW_RED_BITS, 8);
			glfwWindowHint(GLFW_GREEN_BITS, 8);
			glfwWindowHint(GLFW_BLUE_BITS, 8);

			handle = glfwCreateWindow(spec.width, spec.height, spec.title.c_str(), 0, 0);
			if(!handle) {
				GE_Fatal("Could not create window!");
			}
		}
		Window::~Window() {
			glfwDestroyWindow(handle);
		}

		void Window::update() {
			glfwPollEvents();
			glfwSwapBuffers(handle);
		}

		void Window::init() {
			int32 res = glfwInit();
			if(res != GLFW_TRUE) {
				GE_Fatal("Could not initialize GLFW!");
			}
		}
		void Window::release() {
			glfwTerminate();
		}
	}
}
