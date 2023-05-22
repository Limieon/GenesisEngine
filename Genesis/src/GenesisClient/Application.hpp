#pragma once
#include "Defines.hpp"
#include "Window.hpp"

#include <GenesisCore/LayerStack.hpp>
#include <GenesisCore/event/WindowEvent.hpp>

int main(int argc, char** argv);

namespace ge {
	namespace client {
		struct ApplicationConfiguration {
			String name = "Genesis Application";
		};

		class Application {
		public:
			Application(const ApplicationConfiguration& appConfig, const WindowConfiguration& windConfig);
			virtual ~Application();

		private:
			void run();

			bool onWindowClose(ge::core::WindowCloseEvent& e);
			bool onWindowResize(ge::core::WindowResizeEvent& e);

		public:
			void onEvent(ge::core::Event& e);

		public:
			inline static Application& getInstance() { return *instance; }

			inline void pushLayer(ge::core::Layer* layer) { layerStack.pushLayer(layer); }
			inline void pushOverlay(ge::core::Layer* layer) { layerStack.pushOverlay(layer); }
			inline void popLayer(ge::core::Layer* layer) { layerStack.popLayer(layer); }
			inline void popOverlay(ge::core::Layer* layer) { layerStack.popOverlay(layer); }

			inline IWindow& getWindow() const { return *window; }

		private:
			friend int ::main(int argc, char** argv);

		private:
			static Application* instance;

			bool running = true;
			bool minimized = false;

			ge::core::LayerStack layerStack;

			float32 lastTime = 0.f;

			IWindow* window;
		};

		Application* createApplication();
	}
}
