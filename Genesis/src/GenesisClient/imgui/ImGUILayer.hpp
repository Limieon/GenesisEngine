#pragma once
#include <GenesisCore/Layer.hpp>
#include <GenesisCore/event/Event.hpp>
#include <GenesisCore/event/KeyEvent.hpp>
#include <GenesisCore/event/MouseEvent.hpp>
#include <GenesisCore/event/WindowEvent.hpp>

namespace ge {
	namespace client {
		class ImGUILayer: public ge::core::Layer {
		public:
			ImGUILayer(): ge::core::Layer("ImGUI Layer") {}

			void onAttach() override;
			void onDetach() override;

			void begin();
			void end();

		private:
		};
	}
}
