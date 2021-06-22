#pragma once

#include "Core.h"
#include "events/Event.h"
#include "Window.h"

namespace adze {
	class ADZE_API Application {
	public:
		Application();
		~Application();

		void run();
	private:
		std::unique_ptr<Window> window;
		bool running = true;
	};

	// define in client
	Application* createApplication();
}

