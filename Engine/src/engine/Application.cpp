#include "enginepch.h"

#include "Application.h"
#include "engine/events/ApplicationEvent.h"
#include "engine/Log.h"

#include <GLFW/glfw3.h>

namespace engine {
	Application::Application() {
		window = std::unique_ptr<Window>(Window::create());
	}

	Application::~Application() {
	}

	void Application::run() {
		while (running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window->update();
		}
	}
}
