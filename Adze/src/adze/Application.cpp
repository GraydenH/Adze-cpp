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

	void Application::pushLayer(Layer* layer) {
		layerStack.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* layer) {
		layerStack.pushOverlay(layer);
	}

	void Application::run() {
		while (running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : layerStack) {
				layer->update();
			}

			window->update();
		}
	}

	void Application::onEvent(Event& ev) {
		EventDispatcher dispatcher(ev);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));
		for (auto it = layerStack.end(); it != layerStack.begin();) {
			(*--it)->onEvent(ev);
			if (ev.handled) {
				break;
			}
		}

		ADZE_CORE_TRACE("{0}", ev);
	}

	bool Application::onWindowClose(WindowCloseEvent& ev) {
		running = false;
		return true;
	}
}
