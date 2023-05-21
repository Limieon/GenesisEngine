#pragma once
#include "GenesisClient/Defines.hpp"
#include "VertexArray.hpp"

#include <glm/glm.hpp>

#define GE_RENDERER_API_None ge::client::RendererAPI::API::NONE
#define GE_RENDERER_API_OpenGL ge::client::RendererAPI::API::OpenGL

#define GE_getRendererAPI() ge::client::RendererAPI::getAPI()

namespace ge {
	namespace client {
		class RendererAPI {
		public:
			enum class API { NONE = 0, OpenGL = 1 };

		public:
			virtual void init() = 0;

			virtual void drawIndexed(const Ref<IVertexArray>& array, uint32 indexCount = 0) = 0;
			virtual void setClearColor(const glm::vec4& color) = 0;
			virtual void clear() = 0;

			virtual void setViewport(uint32 x, uint32 y, uint32 width, uint32 height) = 0;

			static inline API getAPI() { return api; }

		private:
			static API api;
		};
	}
}
