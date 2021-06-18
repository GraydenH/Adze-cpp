#pragma once

#include "Core.h"
#include "events/Event.h"

namespace engine {
	class ENGINE_API Application {
	public:
		Application();
		~Application();

		void run();
	};

	// define in client
	Application* createApplication();
}

