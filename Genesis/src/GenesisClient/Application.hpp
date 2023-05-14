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

		private:
			friend int ::main(int argc, char** argv);

			bool running;

			Window* window;
		};

		Application* createApplication();
	}
}
