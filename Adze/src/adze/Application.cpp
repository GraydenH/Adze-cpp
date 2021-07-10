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

		float vertices[3 * 3] = {
			-0.5f, -0.5f,  0.0f,
			 0.0f,  0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f,
		};

		vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		vertexBuffer->bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		unsigned int indices[3] = { 0, 1, 2 };

		indexBuffer.reset(IndexBuffer::create(indices, 3));
		indexBuffer->bind();

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;

			out vec3 vPosition;

			void main() {
				vPosition = aPosition;
				gl_Position = vec4(aPosition, 1.0);
			}

		)";
		
		std::string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 vPosition;

			void main() {
				color = vec4(vPosition* 0.5 + 0.5, 1.0);
			}

		)";

		shader.reset(new Shader(vertexSource, fragmentSource));
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

			shader->bind();
			glBindVertexArray(vertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : layerStack) {
				layer->update();
			}

			imguiLayer->begin();
			for (Layer* layer : layerStack) {
				layer->onImguiRender();
			}

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
