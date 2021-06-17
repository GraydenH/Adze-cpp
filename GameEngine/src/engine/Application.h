#pragma once
#include "Core.h"
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

