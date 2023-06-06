#pragma once
#include <GenesisClient/Genesis.hpp>
#include <GenesisCore/Genesis.hpp>
#include <GenesisServer/Genesis.hpp>

namespace runtime {
	class ClientLayer2D: public ge::core::Layer {
	public:
		ClientLayer2D(): Layer("ClientLayer"), camera(16.f / 9.f) {}

		void onAttach() override;
		void onUpdate(ge::core::Timestep ts) override;
		void onDetach() override;

		void onImGUIRender() override;
		void onEvent(ge::core::Event& e) override;

	private:
		ge::client::OrthographicCameraController camera;

		Ref<ge::client::ITexture2D> texture;
	};
}
