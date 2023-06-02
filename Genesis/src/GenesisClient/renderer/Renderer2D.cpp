#include "Renderer2D.hpp"

#include "RenderCommand.hpp"

namespace ge {
	namespace client {
		Renderer2D::Data* Renderer2D::data = nullptr;
		Renderer2D::Stats* Renderer2D::stats = nullptr;

		void Renderer2D::init() {
			data = new Data();
			data->quadVertexArray = IVertexArray::create();
			data->quadVertexBuffer = IVertexBuffer::create(data->maxIndices * sizeof(QuadVertex));
			data->quadVertexBuffer->setLayout({{ShaderDataType::FLOAT3, "a_pos"},
			                                   {ShaderDataType::FLOAT2, "a_uv"},
			                                   {ShaderDataType::FLOAT4, "a_color"},
			                                   {ShaderDataType::FLOAT2, "a_tiling"}});
			data->quadVertexArray->addVertexBuffer(data->quadVertexBuffer);

			data->quadVertexBufferBase = new QuadVertex[data->maxVertices];

			uint32* quadIndices = new uint32[data->maxIndices];
			uint32 offset = 0;
			for(uint32 i = 0; i < data->maxIndices; i += 6) {
				quadIndices[i + 0] = offset + 0;
				quadIndices[i + 1] = offset + 1;
				quadIndices[i + 2] = offset + 2;

				quadIndices[i + 3] = offset + 2;
				quadIndices[i + 4] = offset + 3;
				quadIndices[i + 5] = offset + 0;

				offset += 4;
			}

			Ref<IIndexBuffer> quadIB = IIndexBuffer::create(quadIndices, data->maxIndices);
			data->quadVertexArray->setIndexBuffer(quadIB);
			delete[] quadIndices;

			data->whiteTexture = ITexture2D::create(1, 1);
			uint32 whiteTextureData = 0xFFFFFFFF;
			data->whiteTexture->setData(&whiteTextureData, sizeof(uint32));

			data->texturedShader = IShader::create("shaders/textured.glsl");
			data->texturedShader->bind();
			data->texturedShader->setUniform1i("u_texture", 0);

			data->quadVertexPositions[0] = {-0.5f, -0.5f, 0.f, 1.f};
			data->quadVertexPositions[1] = {0.5f, -0.5f, 0.f, 1.f};
			data->quadVertexPositions[2] = {0.5f, 0.5f, 0.f, 1.f};
			data->quadVertexPositions[3] = {-0.5f, 0.5f, 0.f, 1.f};

			stats = new Stats();
			resetStats();

			flush();
		}
		void Renderer2D::release() { delete data; }
		void Renderer2D::flush() {
			data->quadIndexCount = 0;
			data->quadVertexBufferPtr = data->quadVertexBufferBase;
			data->texture = nullptr;
		}

		void Renderer2D::begin(const OrthographicCamera& cam) {
			data->texturedShader->bind();
			data->texturedShader->setUniformMatrix4fv("u_viewProjectionMatrix", cam.getViewProjectionMatrix());

			data->quadIndexCount = 0;
			data->quadVertexBufferPtr = data->quadVertexBufferBase;

			data->texture = nullptr;

			flush();
		}
		void Renderer2D::end() {
			draw();
			flush();
		}

		void Renderer2D::drawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<ITexture2D>& texture, const glm::vec4& color,
		                          const glm::vec2& tiling) {
			if(data->texture == nullptr) data->texture = texture;
			if(data->quadIndexCount >= data->maxIndices || data->texture != texture) {
				draw();
				flush();
				data->texture = texture;
			}

			data->quadVertexBufferPtr->pos = pos;
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {0.f, 0.f};
			data->quadVertexBufferPtr->tiling = tiling;
			data->quadVertexBufferPtr++;

			data->quadVertexBufferPtr->pos = {pos.x + size.x, pos.y, pos.z};
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {1.f, 0.f};
			data->quadVertexBufferPtr->tiling = tiling;
			data->quadVertexBufferPtr++;

			data->quadVertexBufferPtr->pos = {pos.x + size.x, pos.y + size.y, pos.z};
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {1.f, 1.f};
			data->quadVertexBufferPtr->tiling = tiling;
			data->quadVertexBufferPtr++;

			data->quadVertexBufferPtr->pos = {pos.x, pos.y + size.y, pos.z};
			data->quadVertexBufferPtr->color = color;
			data->quadVertexBufferPtr->uv = {0.f, 1.f};
			data->quadVertexBufferPtr->tiling = tiling;
			data->quadVertexBufferPtr++;
			data->quadIndexCount += 6;

			stats->quadCount++;
		}

		void Renderer2D::draw() {
			size_t dataSize = (uint8*) data->quadVertexBufferPtr - (uint8*) data->quadVertexBufferBase;
			data->quadVertexBuffer->setData(data->quadVertexBufferBase, dataSize);

			data->quadVertexArray->getIndexBuffer()->bind();
			data->texturedShader->bind();
			data->texture->bind();
			RenderCommand::drawIndexed(data->quadVertexArray, data->quadIndexCount);
			stats->drawCalls++;
		}

		void Renderer2D::resetStats() { memset(stats, 0, sizeof(Renderer2D::Stats)); }
		Renderer2D::Stats Renderer2D::getStats() { return *stats; }
	}
}
