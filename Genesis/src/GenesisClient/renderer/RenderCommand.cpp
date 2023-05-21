#include "RenderCommand.hpp"

#include "RendererAPI.hpp"

#ifdef GE_RENDERINGAPI_OPENGL
#	include "GenesisClient/platform/opengl/OpenGLRendererAPI.hpp"
#endif

namespace ge {
	namespace client {
#ifdef GE_RENDERINGAPI_OPENGL
		RendererAPI* RenderCommand::api = new OpenGLRendererAPI();
#endif
	}
}
