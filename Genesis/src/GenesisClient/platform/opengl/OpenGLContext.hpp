#pragma once
#include "GenesisClient/Defines.hpp"
#include "GenesisClient/renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace ge {
	namespace client {
		class OpenGLContext: public IGraphicsContext {
		public:
			OpenGLContext(GLFWwindow* window);
			void init() override;
			void swapBuffers() override;

		private:
			GLFWwindow* window;
		};
	}
}
