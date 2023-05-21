#include "WindowsPlatform.hpp"

#include <GLFW/glfw3.h>

namespace ge {
	namespace client {
		float32 WindowsPlatform::getTimeImpl() const { return glfwGetTime(); }
	}
}
