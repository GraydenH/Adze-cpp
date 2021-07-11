#include "adzepch.h"

#include "Application.h"
#include "adze/Log.h"

#include "adze/Input.h"

#include <glad/glad.h>

namespace adze {

	Application* Application::instance = nullptr;

	static GLenum toOpenglType(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::float1: return GL_FLOAT;
			case ShaderDataType::float2: return GL_FLOAT;
			case ShaderDataType::float3: return GL_FLOAT;
			case ShaderDataType::float4: return GL_FLOAT;
			case ShaderDataType::matrix3: return GL_FLOAT;
			case ShaderDataType::matrix4: return GL_FLOAT;
			case ShaderDataType::integer1: return GL_INT;
			case ShaderDataType::integer2: return GL_INT;
			case ShaderDataType::integer3: return GL_INT;
			case ShaderDataType::integer4: return GL_INT;
			case ShaderDataType::boolean: return GL_BOOL;
		}

		ADZE_CORE_ASSERT(false, "Unknown ShaderDataType!")
		return 0;
	}

	Application::Application() {
		ADZE_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;

		window = std::unique_ptr<Window>(Window::create());
		window->setEventCallback(ADZE_BIND_EVENT_FN(Application::onEvent));
		imguiLayer = new ImguiLayer();
		pushOverlay(imguiLayer);

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		float vertices[7 * 3] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));
		vertexBuffer->bind();

		BufferLayout layout = {
			{ ShaderDataType::float3, "aPosition" },
			{ ShaderDataType::float4, "aColor" },
		};

		vertexBuffer->setLayout(layout);

		uint32_t index = 0;
		for (const auto& element : vertexBuffer->getLayout()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, 
				element.getComponentCount(), 
				toOpenglType(element.type), 
				element.normalized ? GL_TRUE : GL_FALSE, 
				layout.getStride(), 
				(const void *) element.offset
			);
			index++;
		}


		unsigned int indices[3] = { 0, 1, 2 };

		indexBuffer.reset(IndexBuffer::create(indices, 3));
		indexBuffer->bind();

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec4 aColor;

			out vec3 vPosition;
			out vec4 vColor;

			void main() {
				vPosition = aPosition;
				vColor = aColor;
				gl_Position = vec4(aPosition, 1.0);
			}

		)";
		
		std::string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 vPosition;
			in vec4 vColor;

			void main() {
				color = vec4(vPosition* 0.5 + 0.5, 1.0);
				color = vColor; 
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
