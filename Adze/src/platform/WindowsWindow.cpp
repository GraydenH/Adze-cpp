#include "adzepch.h"
#include "WindowsWindow.h"
#include "adze/events/ApplicationEvent.h"
#include "adze/events/KeyEvent.h"
#include "adze/events/MouseEvent.h"

namespace adze {

	static bool glfwInitialized = false;
	
	static void errorCallBack(int error, const char* description) {
		ADZE_CORE_ERROR("error code {0}: {1}", error, description);
	}

	Window* Window::create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		init(props);
	}

	WindowsWindow::~WindowsWindow() {
		shutdown();
	}

	void WindowsWindow::init(const WindowProps& props) {
		data.title = props.title;
		data.width = props.width;
		data.height = props.height;

		ADZE_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!glfwInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			ADZE_CORE_ASSERT(success, "Could not intialize GLFW!");

			glfwSetErrorCallback(errorCallBack);

			glfwInitialized = true;
		}

		window = glfwCreateWindow((int)props.width, (int)props.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		setVSync(true);

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowResizeEvent ev(width, height);
				
			data.eventCallback(ev);
			data.width = width;
			data.height = height;
		});
		
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent ev;
			data.eventCallback(ev);
		});
		
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			if (action == GLFW_PRESS) {
				KeyPressedEvent ev(key, 0);
				data.eventCallback(ev);
			} else if (action == GLFW_RELEASE) {
				KeyReleasedEvent ev(key);
				data.eventCallback(ev);
			} else if (action == GLFW_REPEAT) {
				KeyPressedEvent ev(key, 1);
				data.eventCallback(ev);
			}
		});


		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			if (action == GLFW_PRESS) {
				MouseButtonPressedEvent ev(button);
				data.eventCallback(ev);
			} else if (action == GLFW_RELEASE) {
				MouseButtonReleasedEvent ev(button);
				data.eventCallback(ev);
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			MouseScrolledEvent ev((float) xOffset, (float) yOffset);
			data.eventCallback(ev);
		});
		

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			MouseMovedEvent ev((float) x, (float) y);
			data.eventCallback(ev);
		});
	}

	void WindowsWindow::shutdown() {
		glfwDestroyWindow(window);
	}

	void WindowsWindow::update() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::setVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}

		data.vSync = enabled;
	}

	bool WindowsWindow::isVSync() const {
		return data.vSync;
	}

}