#pragma once
#include "GenesisClient/Defines.hpp"
#include "GenesisClient/renderer/RendererAPI.hpp"

namespace ge {
	namespace client {
		class OpenGLRendererAPI: public RendererAPI {
		public:
			void init() override;

			void drawIndexed(const Ref<IVertexArray>& arr, uint32 indexCount) override;
			void setClearColor(const glm::vec4& color) override;
			void clear() override;

			void setViewport(uint32 x, uint32 y, uint32 width, uint32 height) override;
		};
	}
}
