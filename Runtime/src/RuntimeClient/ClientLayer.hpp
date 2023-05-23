#pragma once
#include <GenesisClient/Genesis.hpp>
#include <GenesisCore/Genesis.hpp>

namespace runtime {
	class ClientLayer: public ge::core::Layer {
	public:
		ClientLayer(): Layer("ClientLayer") {}

		void onAttach() override;
		void onUpdate(ge::core::Timestep ts) override;
		void onDetach() override;

		void onImGUIRender() override;

	private:
		Ref<ge::client::IVertexBuffer> vb;
		Ref<ge::client::IIndexBuffer> ib;
		Ref<ge::client::IVertexArray> va;
		Ref<ge::client::IShader> shader;
		Ref<ge::client::ITexture> texture;
	};
}
