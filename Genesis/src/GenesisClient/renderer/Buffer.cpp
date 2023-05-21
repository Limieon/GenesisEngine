#include "Buffer.hpp"

#include "GenesisClient/platform/opengl/OpenGLBuffer.hpp"
#include "RendererAPI.hpp"

namespace ge {
	namespace client {
		Ref<IVertexBuffer> IVertexBuffer::create(const void* data, size_t size) {
			switch(GE_getRendererAPI()) {
				case GE_RENDERER_API_None: std::exit(-1); return nullptr;
				case GE_RENDERER_API_OpenGL: return createRef<OpenGLVertexBuffer>(data, size);
			}
			return nullptr;
		}
		Ref<IVertexBuffer> IVertexBuffer::create(size_t size) {
			switch(GE_getRendererAPI()) {
				case GE_RENDERER_API_None: std::exit(-1); return nullptr;
				case GE_RENDERER_API_OpenGL: return createRef<OpenGLVertexBuffer>(size);
			}
			return nullptr;
		}

		Ref<IIndexBuffer> IIndexBuffer::create(uint32* indices, uint32 count) {
			switch(GE_getRendererAPI()) {
				case GE_RENDERER_API_None: std::exit(-1); return nullptr;
				case GE_RENDERER_API_OpenGL: return createRef<OpenGLIndexBuffer>(indices, count);
			}
		}
	}
}
