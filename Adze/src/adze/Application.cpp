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
		imguiLayer = new ImguiLayer();
		pushOverlay(imguiLayer);

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);
		
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f,  0.0f,
			 0.0f,  0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(vertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : layerStack) {
				layer->update();
			}

			imguiLayer->begin();
			for (Layer* layer : layerStack)
				layer->onImguiRender();
			imguiLayer->end();
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
	}

	bool Application::onWindowClose(WindowCloseEvent& ev) {
		running = false;
		return true;
	}
}
