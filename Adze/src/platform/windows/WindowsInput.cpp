#include "adzepch.h"
#include "WindowsInput.h"

#include "adze/Application.h"

#include <GLFW/glfw3.h>

namespace adze {

	Input* Input::instance = new WindowsInput();

	bool WindowsInput::isKeyPressedImpl(int keyCode) {
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::isMouseButtonPressedImpl(int button) {
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	float WindowsInput::getMouseXImpl() {
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		double x;
		double y;

		glfwGetCursorPos(window, &x, &y);
		return (float) x;
	}
	float WindowsInput::getMouseYImpl() {
		auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
		double x;
		double y;

		glfwGetCursorPos(window, &x, &y);
		return (float) y;
	}
}