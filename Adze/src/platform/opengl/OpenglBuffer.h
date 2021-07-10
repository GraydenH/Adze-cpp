#pragma once

#include "adze/renderer/Buffer.h"

namespace adze {
	class OpenglVertexBuffer : public VertexBuffer {
	public:
		OpenglVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenglVertexBuffer();

		virtual void bind() const;
		virtual void unbind() const;
	private:
		uint32_t rendererId;
	};
	
	class OpenglIndexBuffer : public IndexBuffer {
	public:
		OpenglIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenglIndexBuffer();

		virtual void bind() const;
		virtual void unbind() const;
	private:
		uint32_t rendererId;
		uint32_t count;
	};
}