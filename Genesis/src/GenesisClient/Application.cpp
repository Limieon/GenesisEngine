#include "Application.hpp"
#include <iostream>

#include <GenesisCore/Logger.hpp>

namespace ge {
	namespace client {
		Application::Application(const ApplicationConfiguration& appConfig, const WindowConfiguration& windConfig) {
			ge::core::Logger::init();

			GE_Info("Intializing Engine Components...");
			Window::init();

			window = new Window(windConfig);
		}
		Application::~Application() {
			delete window;
		}

		void Application::run() {
			GE_Info("Starting application...");

			while(!glfwWindowShouldClose(window->getHandle())) {
				window->update();
			}

			ge::core::Logger::release();
		}
	}
}
