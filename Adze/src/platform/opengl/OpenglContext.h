#pragma once

#include "adze/renderer/RenderContext.h"
#include <GLFW/glfw3.h>

#include <glad/glad.h>
#include <gl/GL.h>

namespace adze {
	class OpenglContext : public RenderContext {
	public:
		OpenglContext(GLFWwindow* window);
		void init() override;
		void swapBuffers() override;
	private:
		GLFWwindow* window;
	};
}