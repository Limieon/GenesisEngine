#include "LayerStack.hpp"

namespace ge {
	namespace core {
		LayerStack::~LayerStack() {
			for(Layer* l: layers) {
				l->onDetach();
				delete l;
			}
		}

		void LayerStack::pushLayer(Layer* layer) {
			layers.emplace(layers.begin() + layerInsertIndex, layer);
			layer->onAttach();
			layerInsertIndex++;
		}
		void LayerStack::pushOverlay(Layer* layer) {
			layers.emplace_back(layer);
			layer->onAttach();
		}
		void LayerStack::popLayer(Layer* layer) {
			auto it = std::find(layers.begin(), layers.begin() + layerInsertIndex, layer);
			if(it != layers.begin() + layerInsertIndex) {
				layer->onDetach();
				layers.erase(it);
				layerInsertIndex--;
			}
		}
		void LayerStack::popOverlay(Layer* layer) {
			auto it = std::find(layers.begin() + layerInsertIndex, layers.end(), layer);
			if(it != layers.end()) {
				layer->onDetach();
				layers.erase(it);
			}
		}
	}
}
