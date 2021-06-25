#pragma once

#include "adze/Layer.h"
#include <adze/events/MouseEvent.h>
#include <adze/events/KeyEvent.h>
#include <adze/events/ApplicationEvent.h>

namespace adze {

	class ADZE_API ImguiLayer : public Layer {
	public:
		ImguiLayer();
		~ImguiLayer();

		virtual void attach() override;
		virtual void detach() override;
		virtual void update() override;

		virtual void onImguiRender() override;
		void begin();
		void end();
	private:
		float time = 0.0f;
	};

} 