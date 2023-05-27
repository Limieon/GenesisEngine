#include "ClientLayer.hpp"

#include <imgui.h>

struct Vertex {
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec4 color;
};

namespace runtime {
	void ClientLayer::onAttach() {
		GE_Info("Client layer attached!");

		ge::client::RenderCommand::setClearColor({0.f, 0.f, 0.f, 1.f});
		texture = ge::client::ITexture2D::create("textures/texture.png");
	}
	void ClientLayer::onUpdate(ge::core::Timestep ts) {
		ge::client::RenderCommand::clear();
		ge::client::Renderer2D::resetStats();
		camera.onUpdate(ts);

		ge::client::Renderer2D::begin(camera.getCamera());
		ge::client::Renderer2D::drawQuad({1.f, 1.f}, {5.f, 5.f}, texture);
		ge::client::Renderer2D::drawQuad({7.f, 2.f}, {9.f, 7.f}, {1.f, 0.f, 1.f, 1.f});
		ge::client::Renderer2D::drawQuad({10.f, 14.f}, {12.f, 12.f}, texture, {0.f, 0.f, 1.f, 1.f});
		ge::client::Renderer2D::end();
	}
	void ClientLayer::onDetach() { GE_Info("Client layer detached!"); }

	void ClientLayer::onEvent(ge::core::Event& e) { camera.onEvent(e); }

	void ClientLayer::onImGUIRender() {
		bool open = true;
		auto stats = ge::client::Renderer2D::getStats();

		ImGui::Begin("Renderer2D Stats", &open);
		ImGui::Text("Draw Calls: %i", (int32) stats.drawCalls);
		ImGui::Text("Quads: %i", (int32) stats.quadCount);
		ImGui::Text("Vertices: %i", (int32) stats.getVertexCount());
		ImGui::Text("Indices: %i", (int32) stats.getIndicesCount());
		ImGui::End();
	}
}
