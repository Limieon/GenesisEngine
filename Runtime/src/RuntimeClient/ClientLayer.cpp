#include "ClientLayer.hpp"

#include <imgui.h>

struct Vertex {
	glm::vec3 pos;
	glm::vec4 color;
};

namespace runtime {
	void ClientLayer::onAttach() {
		GE_Info("Client layer attached!");

		ge::client::RenderCommand::setClearColor({0.f, 0.f, 0.f, 1.f});

		texture = ge::client::ITexture2D::create("textures/texture.png");

		ge::server::Voxel* voxel = new ge::server::Voxel("voxel");
		ge::server::Voxel* voxel2 = new ge::server::Voxel("voxel2");
		ge::server::Voxel* voxel3 = new ge::server::Voxel("voxel3");

		ge::server::GameRegistry::registerVoxel(voxel);
		ge::server::GameRegistry::registerVoxel(voxel2);
		ge::server::GameRegistry::registerVoxel(voxel3);
		ge::server::GameRegistry::debugPrintData();

		GE_Info("VoxelID: {}", ge::server::GameRegistry::getVoxelID(voxel2->getUnlocalizedName()));

		ge::server::Chunk chunk;
		chunk.set(3, 2, 5, ge::server::GameRegistry::getVoxelID(voxel3->getUnlocalizedName()));
		GE_Info("Voxel [3, 2, 5]: {}", ge::server::GameRegistry::getUnlocalizedName(chunk.getVoxel(3, 2, 5)));

		GE_Info(voxel->getUnlocalizedName());

		ge::server::GameRegistry::release();
		delete voxel;
		delete voxel2;
		delete voxel3;
	}
	void ClientLayer::onUpdate(ge::core::Timestep ts) {
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
	void ClientLayer::onDetach() { GE_Info("Client layer detached!"); }

	void ClientLayer::onEvent(ge::core::Event& e) { camera.onEvent(e); }

	void ClientLayer::onImGUIRender() {
		auto stats = ge::client::Renderer2D::getStats();

		ImGui::Begin("Renderer2D Stats", nullptr);
		ImGui::Text("Draw Calls: %i", (int32) stats.drawCalls);
		ImGui::Text("Quads: %i", (int32) stats.quadCount);
		ImGui::Text("Vertices: %i", (int32) stats.getVertexCount());
		ImGui::Text("Indices: %i", (int32) stats.getIndicesCount());
		ImGui::End();
	}
}
