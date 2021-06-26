#include "adzepch.h"
#include "OpenglContext.h"

adze::OpenglContext::OpenglContext(GLFWwindow* window) : window(window) {
	ADZE_CORE_ASSERT(window, "Window is null!");
}

void adze::OpenglContext::init() {
		glfwMakeContextCurrent(window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ADZE_CORE_ASSERT(status, "Failed to initialize Glad!");

		ADZE_CORE_INFO("opengl info");
		ADZE_CORE_INFO("vendor: {0}", glGetString(GL_VENDOR));
		ADZE_CORE_INFO("renderer: {0}", glGetString(GL_RENDERER));
		ADZE_CORE_INFO("version: {0}", glGetString(GL_VERSION));
}

void adze::OpenglContext::swapBuffers() {
	glfwSwapBuffers(window);
}
