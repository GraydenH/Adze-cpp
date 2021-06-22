#include "adzepch.h"

#include "Application.h"
#include "adze/events/ApplicationEvent.h"
#include "adze/Log.h"

#include <GLFW/glfw3.h>

namespace adze {
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
