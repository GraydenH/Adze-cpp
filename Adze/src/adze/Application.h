#pragma once

#include "Core.h"
#include "events/Event.h"
#include "Window.h"
#include "adze/events/ApplicationEvent.h"

#include "adze/LayerStack.h"

namespace adze {
	class ADZE_API Application {
	public:
		Application();
		~Application();

		void run();
		void onEvent(Event& ev);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);
	private:
		bool onWindowClose(WindowCloseEvent& ev);

		std::unique_ptr<Window> window;
		bool running = true;
		
		LayerStack layerStack;
	};

	// define in client
	Application* createApplication();
}

