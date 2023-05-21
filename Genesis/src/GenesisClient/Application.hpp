#pragma once
#include "Defines.hpp"
#include "Window.hpp"

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
			void run();

			void onEvent(ge::core::Event& e);

		private:
			friend int ::main(int argc, char** argv);

		private:
			static Application* instance;

			bool running = true;
			bool minimized = false;

			IWindow* window;
			float32 lastTime = 0.f;
		};

		Application* createApplication();
	}
}
