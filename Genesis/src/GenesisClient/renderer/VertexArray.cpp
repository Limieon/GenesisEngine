#include "VertexArray.hpp"

#include "GenesisClient/platform/opengl/OpenGLVertexArray.hpp"
#include "RendererAPI.hpp"

namespace ge {
	namespace client {
		Ref<IVertexArray> IVertexArray::create() {
			switch(GE_getRendererAPI()) {
				case GE_RENDERER_API_None: std::exit(-1); return nullptr;
				case GE_RENDERER_API_OpenGL: return createRef<OpenGLVertexArray>();
			}
			return nullptr;
		}
	}
}
