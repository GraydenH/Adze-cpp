#pragma once

#include "Core.h"
#include "events/Event.h"
#include "Window.h"
#include "adze/events/ApplicationEvent.h"

#include "adze/imgui/ImguiLayer.h"
#include "adze/LayerStack.h"
#include <adze/Shader.h>

namespace adze {
	class ADZE_API Application {
	public:
		Application();
		~Application();

		void run();
		void onEvent(Event& ev);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);

		inline Window& getWindow() { return *window; }
		inline static Application& get() { return *instance; }
	private:
		bool onWindowClose(WindowCloseEvent& ev);

		std::unique_ptr<Window> window;
		ImguiLayer* imguiLayer;
		bool running = true;

		LayerStack layerStack;

		static Application* instance;

		unsigned int vertexArray;
		unsigned int vertexBuffer;
		unsigned int indexBuffer;

		std::unique_ptr<Shader> shader;

	};


	// define in client
	Application* createApplication();
}

