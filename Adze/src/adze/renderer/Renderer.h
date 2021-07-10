#pragma once

namespace adze {

	enum class RendererApi {
		None = 0, OpenGL = 1
	};

	class Renderer {
	public:
		inline static RendererApi GetAPI() { return rendererApi; }
	private:
		static RendererApi rendererApi;
	};
}