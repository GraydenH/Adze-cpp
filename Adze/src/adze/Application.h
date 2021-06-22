#pragma once

#include "Core.h"
#include "events/Event.h"
#include "Window.h"
#include "adze/events/ApplicationEvent.h"

namespace adze {
	class ADZE_API Application {
	public:
		Application();
		~Application();

		void run();
		void onEvent(Event& ev);
		bool onWindowClose(WindowCloseEvent& ev);
	private:
		std::unique_ptr<Window> window;
		bool running = true;
	};

	// define in client
	Application* createApplication();
}

