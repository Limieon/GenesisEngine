#include "ClientLayer2D.hpp"

#include <imgui.h>

struct Vertex {
	glm::vec3 pos;
	glm::vec4 color;
};

namespace runtime {
	void ClientLayer2D::onAttach() {
		GE_Info("Client layer attached!");

		ge::client::RenderCommand::setClearColor({0.f, 0.f, 0.f, 1.f});

		texture = ge::client::ITexture2D::create("textures/texture.png");
	}
	void ClientLayer2D::onUpdate(ge::core::Timestep ts) {
		ge::client::RenderCommand::clear();
		camera.onUpdate(ts);

		ge::client::Renderer2D::resetStats();
		ge::client::Renderer2D::begin(camera.getCamera());
		for(uint32 x = 0; x < 300; ++x) {
			for(uint32 y = 0; y < 300; ++y) {
				ge::client::Renderer2D::drawQuad({x, y}, {0.9f, 0.9f}, texture, {x / 300.f, 0.f, y / 300.f, 1.f});
			}
		}
		ge::client::Renderer2D::end();
	}
	void ClientLayer2D::onDetach() { GE_Info("Client layer detached!"); }

	void ClientLayer2D::onEvent(ge::core::Event& e) { camera.onEvent(e); }

	void ClientLayer2D::onImGUIRender() {
		auto stats = ge::client::Renderer2D::getStats();

		ImGui::Begin("Renderer2D Stats", nullptr);
		ImGui::Text("Draw Calls: %i", (int32) stats.drawCalls);
		ImGui::Text("Quads: %i", (int32) stats.quadCount);
		ImGui::Text("Vertices: %i", (int32) stats.getVertexCount());
		ImGui::Text("Indices: %i", (int32) stats.getIndicesCount());
		ImGui::End();
	}
}
