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

		void attach();
		void detach();
		void update();
		void onEvent(Event& event);
	private:
		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool onMouseMovedEvent(MouseMovedEvent& e);
		bool onMouseScrolledEvent(MouseScrolledEvent& e);
		bool onKeyPressedEvent(KeyPressedEvent& e);
		bool onKeyReleasedEvent(KeyReleasedEvent& e);
		bool onKeyTypedEvent(KeyTypedEvent& e);
		bool onWindowResizeEvent(WindowResizeEvent& e);

		float time = 0.0f;
	};

} 