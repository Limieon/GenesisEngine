#include "Renderer.hpp"

#include "RenderCommand.hpp"
#include "Renderer2D.hpp"
#include "RendererAPI.hpp"

namespace ge {
	namespace client {
		Renderer::Data* Renderer::sceneData = nullptr;

		void Renderer::init() {
			sceneData = new Renderer::Data();
			Renderer2D::init();
		}
		void Renderer::release() {
			Renderer2D::release();
			delete sceneData;
		}

		void Renderer::beginScene(Camera& camera) { sceneData->viewProjectionMatrix = camera.getViewProjectionMatrix(); }
		void Renderer::endScene() {}

		void Renderer::submit(const Ref<IShader>& shader, const Ref<IVertexArray>& vertexArray, const Ref<IIndexBuffer> indexBuffer) {
			shader->bind();
			shader->setUniformMatrix4fv("u_viewProjectionMatrix", sceneData->viewProjectionMatrix);

			vertexArray->bind();
			indexBuffer->bind();

			RenderCommand::drawIndexed(vertexArray, indexBuffer->getCount());
		}
	}
}
