#pragma once
#include <cstdint>

namespace adze {
	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static VertexBuffer* create(float* vertices, uint32_t size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static IndexBuffer* create(uint32_t* vertices, uint32_t count);
	};
}
