#pragma once

#include "adze/renderer/Buffer.h"

namespace adze {
	class OpenglVertexBuffer : public VertexBuffer {
	public:
		OpenglVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenglVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const BufferLayout& getLayout() const override { return layout; };
		virtual void setLayout(const BufferLayout& value) override {layout = value; };
	private:
		uint32_t rendererId;
		BufferLayout layout;
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