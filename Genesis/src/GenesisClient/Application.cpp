#include "Application.hpp"

#include "renderer/RenderCommand.hpp"
#include "renderer/RendererAPI.hpp"

#include <GenesisCore/Logger.hpp>
#include <GenesisCore/event/KeyEvent.hpp>
#include <iostream>

namespace ge {
	namespace client {
		Application* Application::instance = nullptr;

		Application::Application(const ApplicationConfiguration& appConfig, const WindowConfiguration& windConfig) {
			ge::core::Logger::init();

			GE_Info("Intializing Engine Components...");
			window = IWindow::create(windConfig);
			window->setEventCallback(GE_BindEventFunction(Application::onEvent));
			window->setVSync(true);
		}
		Application::~Application() { delete window; }

		void Application::onEvent(ge::core::Event& e) {
			if(e.getEventType() == ge::core::EventType::KeyDown) {
				auto keyEvent = (ge::core::KeyTypedEvent&) e;
				GE_Info("Key Down Event Fired: {}", keyEvent.getKeyCode());
				return;
			}

			GE_Info("Event Fired: {}", e.getName());
		}

		void Application::run() {
			GE_Info("Starting application...");

			while(running) {
				window->onUpdate();
			}

			ge::core::Logger::release();
		}
	}
}
