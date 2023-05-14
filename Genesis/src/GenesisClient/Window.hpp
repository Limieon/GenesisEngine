#pragma once
#include <GenesisCore/Defines.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace ge {
	namespace client {
		struct WindowConfiguration {
			String title = "Genesis Application ";
			uint16 width = 800;
			uint16 height = 600;
		};

		class Window {
		public:
			Window(const WindowConfiguration& spec);
			~Window();

			void update();
			GLFWwindow* getHandle() const { return handle; }

			static void init();
			static void release();

		private:
			GLFWwindow* handle;
		};
	}
}
