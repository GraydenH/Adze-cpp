#include "adzepch.h"

#include "Application.h"
#include "adze/Log.h"

#include <GLFW/glfw3.h>

namespace adze {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application() {
		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
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

	void Application::onEvent(Event& ev) {
		EventDispatcher dispatcher(ev);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));

		ADZE_CORE_TRACE("{0}", ev);
	}

	bool Application::onWindowClose(WindowCloseEvent& ev) {
		running = false;
		return true;
	}
}
