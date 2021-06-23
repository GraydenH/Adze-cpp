#include "adzepch.h"
#include "LayerStack.h"

namespace adze {
	LayerStack::LayerStack() {
	}

	LayerStack::~LayerStack() {
		for (Layer* layer :layers) {
			layer->detach();
			delete layer;
		}
	}

	void LayerStack::pushLayer(Layer* layer) {
		layers.emplace(layers.begin() + layerInsertIndex, layer);
		layerInsertIndex++;
	}

	void LayerStack::pushOverlay(Layer* overlay) {
		layers.emplace_back(overlay);
	}

	void LayerStack::popLayer(Layer* layer) {
		auto it = std::find(layers.begin(), layers.begin() + layerInsertIndex, layer);
		if (it != layers.begin() + layerInsertIndex) {
			layer->detach();
			layers.erase(it);
			layerInsertIndex--;
		}
	}

	void LayerStack::popOverlay(Layer* overlay) {
		auto it = std::find(layers.begin() + layerInsertIndex, layers.end(), overlay);
		if (it != layers.end()) {
			overlay->detach();
			layers.erase(it);
		}
	}

} 