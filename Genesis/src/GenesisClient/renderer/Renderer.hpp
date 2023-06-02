#pragma once
#include "Buffer.hpp"
#include "Renderer2D.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

namespace ge {
	namespace client {
		class Renderer {
		public:
			struct Data {
				glm::mat4 viewProjectionMatrix;
			};

			static void init();
			static void release();

			static void beginScene(Camera& camera);
			static void endScene();

			static void submit(const Ref<IShader>& shader, const Ref<IVertexArray>& vertexArray, const Ref<IIndexBuffer> indexBuffer);

		private:
			static Renderer::Data* sceneData;
		};
	}
}
