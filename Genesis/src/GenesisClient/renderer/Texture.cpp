#include "Texture.hpp"

#include "GenesisClient/platform/opengl/OpenGLTexture.hpp"
#include "RendererAPI.hpp"

namespace ge {
	namespace client {
		Ref<ITexture2D> ITexture2D::create(const String& path) {
			switch(RendererAPI::getAPI()) {
				case RendererAPI::API::NONE: GE_Assert(false, "RendererAPI::None is currently not supported!");
				case RendererAPI::API::OpenGL: return createRef<OpenGLTexture2D>(path);
			}
			return nullptr;
		}

		Ref<ITexture2D> ITexture2D::create(uint32 width, uint32 height) {
			switch(RendererAPI::getAPI()) {
				case RendererAPI::API::NONE: GE_Assert(false, "RendererAPI::None is currently not supported!");
				case RendererAPI::API::OpenGL: return createRef<OpenGLTexture2D>(width, height);
			}
			return nullptr;
		}
	}
}
