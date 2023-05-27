#pragma once
#include "Buffer.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"

#include <glm/glm.hpp>

namespace ge {
	namespace client {
		class Renderer2D {
		public:
			struct Stats {
				uint32 quadCount;
				uint32 drawCalls;

				uint32 getVertexCount() { return quadCount * 4; }
				uint32 getIndicesCount() { return quadCount * 6; }
			};

			struct QuadVertex {
				glm::vec3 pos;
				glm::vec2 uv;
				glm::vec4 color;
				glm::vec2 tiling;
			};

			struct Data {
				const uint32 maxQuads = 50000;
				const uint32 maxVertices = maxQuads * 4;
				const uint32 maxIndices = maxQuads * 6;
				static const uint32 maxTextureSlots = 32;

				Ref<IVertexArray> quadVertexArray;
				Ref<IVertexBuffer> quadVertexBuffer;
				Ref<ITexture2D> whiteTexture;
				Ref<IShader> texturedShader;

				uint32 quadIndexCount;
				QuadVertex* quadVertexBufferBase = nullptr;
				QuadVertex* quadVertexBufferPtr = nullptr;

				Ref<ITexture2D> texture = nullptr;

				glm::vec4 quadVertexPositions[4];
			};

			Renderer2D() = delete;

			static void init();
			static void release();
			static void flush();

			static void begin(const OrthographicCamera& cam);
			static void end();

			static inline void drawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, const glm::vec2& tiling = {1.f, 1.f}) {
				drawQuad({pos.x, pos.y, 0.f}, size, data->whiteTexture, color, tiling);
			};
			static inline void drawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<ITexture2D>& texture,
			                            const glm::vec2& tiling = {1.f, 1.f}) {
				drawQuad({pos.x, pos.y, 0.f}, size, texture, {1.f, 1.f, 1.f, 1.f}, tiling);
			};
			static inline void drawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<ITexture2D>& texture, const glm::vec4& color,
			                            const glm::vec2& tiling = {1.f, 1.f}) {
				drawQuad({pos.x, pos.y, 0.f}, size, texture, color, tiling);
			}

			static void drawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<ITexture2D>& texture, const glm::vec4& color,
			                     const glm::vec2& tiling = {1.f, 1.f});

			static void resetStats();
			static Stats getStats();

		private:
			static Renderer2D::Data* data;
			static Renderer2D::Stats* stats;

			static void draw();
		};
	}
}
