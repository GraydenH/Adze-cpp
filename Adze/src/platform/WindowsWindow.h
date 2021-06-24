#pragma once

#include "adze/Window.h"

#include <GLFW/glfw3.h>

namespace adze {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void update() override;

		inline unsigned int getWidth() const override { return data.width; }
		inline unsigned int getHeight() const override { return data.height; }

		// Window attributes
		inline void setEventCallback(const EventCallback& callback) override { data.eventCallback = callback; }
		
		void setVSync(bool enabled) override;
		bool isVSync() const override;
		
		inline virtual void* getNativeWindow() const override { return window; };
	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();
	private:
		GLFWwindow* window;

		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool vSync;

			EventCallback eventCallback;
		};

		WindowData data;
	};

} 