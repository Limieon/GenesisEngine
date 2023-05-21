#include "GenesisClient/platform/opengl/OpenGLContext.hpp"

#include "OpenGLError.hpp"

#include <GLFW/glfw3.h>
#include <GenesisCore/Config.hpp>
#include <GenesisCore/Logger.hpp>
#include <glad/glad.h>

namespace ge {
	namespace client {
		OpenGLContext::OpenGLContext(GLFWwindow* window): window(window) {
			if(window == nullptr) std::cerr << "Window cannot be null!" << std::endl;
		}

		void OpenGLContext::init() {
			// Set context and initialize glad
			glfwMakeContextCurrent(window);
			if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
				GE_Fatal("Failed to initialize glad!");
			}

			if(GLVersion.major < 4 || (GLVersion.major != 4 && GLVersion.minor < 5)) {
				GE_Fatal("Genesis Engine atleast needs OpenGL 4.5!");
			}

// Enable OpenGL Debug Callback
#if GE_CONFIG_GL_DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(openGLDebugCallback, 0);
#endif

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			glEnable(GL_COLOR_MATERIAL);

			// Sets the clear color to a standard
			// Does not need to use RenderComand abstraction because
			// this code will only be ran if OpenGL is the selected
			// renderer api
			glClearColor(0.f, 0.f, 0.f, 1.f);
		}
		void OpenGLContext::swapBuffers() { glfwSwapBuffers(window); }
	}
}
