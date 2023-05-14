#pragma once

int main(int argc, char** argv);

namespace ge {
	namespace client {
		class Application {
		public:
			Application();
			virtual ~Application();

			void run();

		private:
			friend int ::main(int argc, char** argv);
		};

		Application* createApplication();
	}
}
