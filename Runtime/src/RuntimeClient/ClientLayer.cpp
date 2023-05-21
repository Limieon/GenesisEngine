#include "ClientLayer.hpp"

struct Vertex {
	glm::vec3 pos;
	glm::vec4 color;
};

namespace runtime {
	void ClientLayer::onAttach() {
		GE_Info("Client layer attached!");

		std::vector<Vertex> vertices;
		vertices.push_back({{-.5f, .5f, .0f}, {1.f, 0.f, 0.f, 1.f}});
		vertices.push_back({{-.5f, -.5f, .0f}, {0.f, 1.f, 0.f, 1.f}});
		vertices.push_back({{.5f, -.5f, .0f}, {0.f, 0.f, 1.f, 1.f}});
		vertices.push_back({{.5f, .5f, .0f}, {1.f, 0.f, 1.f, 1.f}});

		uint32 indices[] = {0, 1, 2, 2, 3, 0};

		va = ge::client::IVertexArray::create();
		vb = ge::client::IVertexBuffer::create(vertices.data(), vertices.size() * sizeof(Vertex));
		vb->setLayout({{ge::client::ShaderDataType::FLOAT3, "a_pos"}, {ge::client::ShaderDataType::FLOAT4, "a_color"}});

		ib = ge::client::IIndexBuffer::create(indices, 6);
		va->addVertexBuffer(vb);
		va->setIndexBuffer(ib);

		shader = ge::client::IShader::create("shaders/basic.glsl");
	}
	void ClientLayer::onUpdate(ge::core::Timestep ts) {
		ge::client::RenderCommand::clear();

		shader->bind();
		va->bind();
		ge::client::RenderCommand::drawIndexed(va, va->getIndexBuffer()->getCount());
	}
	void ClientLayer::onDetach() { GE_Info("Client layer detached!"); }
}
