#include "GraphicsContext.hpp"

#ifdef GE_RENDERINGAPI_OPENGL
#	include "GenesisClient/platform/opengl/OpenGLContext.hpp"
#	include <GLFW/glfw3.h>
#else
#	error Undefined RenderingAPI! Currently only OpenGL is supported!
#endif

namespace ge {
	namespace client {
		IGraphicsContext* IGraphicsContext::create(void* window) {
#ifdef GE_RENDERINGAPI_OPENGL
			return new ge::client::OpenGLContext((GLFWwindow*) window);
#endif
			return nullptr;
		}
	}
}
