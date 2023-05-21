#pragma once
#include "Buffer.hpp"
#include "GenesisClient/Defines.hpp"
#include "RendererAPI.hpp"

namespace ge {
	namespace client {
		class RenderCommand {
		public:
			inline static void init() { api->init(); }

			inline static void drawIndexed(const Ref<IVertexArray>& arr, uint32 indexCount = 0) { api->drawIndexed(arr, indexCount); }
			inline static void setClearColor(const glm::vec4& color) { api->setClearColor(color); }
			inline static void clear() { api->clear(); }

			inline static void setViewport(uint32 x, uint32 y, uint32 width, uint32 height) { api->setViewport(x, y, width, height); }

		private:
			static RendererAPI* api;
		};
	}
}
