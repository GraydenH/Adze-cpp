#pragma once

#include "adze/Layer.h"

namespace adze {

	class ADZE_API ImguiLayer : public Layer {
	public:
		ImguiLayer();
		~ImguiLayer();

		void attach();
		void detach();
		void update();
		void onEvent(Event& event);
	private:
		float time = 0.0f;
	};

} 