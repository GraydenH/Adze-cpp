#include "adzepch.h"

#include "Application.h"
#include "adze/Log.h"

#include "adze/Input.h"

#include <glad/glad.h>

namespace adze {

	Application* Application::instance = nullptr;

	Application::Application() {
		ADZE_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;

		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(ADZE_BIND_EVENT_FN(Application::onEvent));
	}

	Application::~Application() {
	}

	void Application::pushLayer(Layer* layer) {
		layerStack.pushLayer(layer);
		layer->attach();
	}

	void Application::pushOverlay(Layer* layer) {
		layerStack.pushOverlay(layer);
		layer->attach();
	}

	void Application::run() {
		while (running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : layerStack) {
				layer->update();
			}

			ADZE_CORE_TRACE("{0}, {1}", Input::getMouseX(), Input::getMouseY());

			window->update();
		}
	}

	void Application::onEvent(Event& ev) {
		EventDispatcher dispatcher(ev);
		dispatcher.dispatch<WindowCloseEvent>(ADZE_BIND_EVENT_FN(Application::onWindowClose));

		for (auto it = layerStack.rbegin(); it != layerStack.rend(); ++it) {
			if (ev.handled) {
				break;
			}
			(*it)->onEvent(ev);
		}

		ADZE_CORE_TRACE("{0}", ev);
	}

	bool Application::onWindowClose(WindowCloseEvent& ev) {
		running = false;
		return true;
	}
}
