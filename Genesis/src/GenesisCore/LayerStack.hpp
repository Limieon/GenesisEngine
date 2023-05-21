#pragma once
#include "GenesisCore/Layer.hpp"

namespace ge {
	namespace core {
		class LayerStack {
		public:
			LayerStack() = default;
			~LayerStack();

			void pushLayer(Layer* layer);
			void pushOverlay(Layer* layer);
			void popLayer(Layer* layer);
			void popOverlay(Layer* layer);

			inline std::vector<Layer*>::iterator begin() { return layers.begin(); }
			inline std::vector<Layer*>::iterator end() { return layers.end(); }
			inline std::vector<Layer*>::reverse_iterator rbegin() { return layers.rbegin(); }
			inline std::vector<Layer*>::reverse_iterator rend() { return layers.rend(); }

			inline std::vector<Layer*>::const_iterator begin() const { return layers.begin(); }
			inline std::vector<Layer*>::const_iterator end() const { return layers.end(); }
			inline std::vector<Layer*>::const_reverse_iterator rbegin() const { return layers.rbegin(); }
			inline std::vector<Layer*>::const_reverse_iterator rend() const { return layers.rend(); }

		private:
			std::vector<Layer*> layers;
			uint32 layerInsertIndex = 0;
		};
	}
}
