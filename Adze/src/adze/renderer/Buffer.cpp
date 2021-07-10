#include "adzepch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "platform/opengl/OpenglBuffer.h"

namespace adze {
	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererApi::None:    ADZE_CORE_ASSERT(false, "RendererApi::None is currently not supported!"); return nullptr;
			case RendererApi::OpenGL:  return new OpenglVertexBuffer(vertices, size);
		}

		ADZE_CORE_ASSERT(false, "Unknown RendererApi!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t count) {
		switch (Renderer::GetAPI())
		{
			case RendererApi::None:    ADZE_CORE_ASSERT(false, "RendererApi::None is currently not supported!"); return nullptr;
			case RendererApi::OpenGL:  return new OpenglIndexBuffer(indices, count);
		}

		ADZE_CORE_ASSERT(false, "Unknown RendererApi!");
		return nullptr;
	}
}