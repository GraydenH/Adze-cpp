#include "adzepch.h"
#include "OpenglBuffer.h"

#include <glad/glad.h>

adze::OpenglVertexBuffer::OpenglVertexBuffer(float* vertices, uint32_t size) {
	glCreateBuffers(1, &rendererId);
	glBindBuffer(GL_ARRAY_BUFFER, rendererId);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

adze::OpenglVertexBuffer::~OpenglVertexBuffer() {
	glDeleteBuffers(1, &rendererId);
}

void adze::OpenglVertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, rendererId);
}

void adze::OpenglVertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

adze::OpenglIndexBuffer::OpenglIndexBuffer(uint32_t* indices, uint32_t count) : count(count) {
	glCreateBuffers(1, &rendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

adze::OpenglIndexBuffer::~OpenglIndexBuffer() {
	glDeleteBuffers(1, &rendererId);
}

void adze::OpenglIndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererId);
}

void adze::OpenglIndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
