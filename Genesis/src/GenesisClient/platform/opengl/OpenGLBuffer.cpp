#include "OpenGLBuffer.hpp"

#include "OpenGLError.hpp"

#include <glad/glad.h>

namespace ge {
	namespace client {
		OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size) {
			glCheck(glCreateBuffers(1, &handle));
			glCheck(glBindBuffer(GL_ARRAY_BUFFER, handle));
			glCheck(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
		}
		OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, size_t size) {
			glCheck(glCreateBuffers(1, &handle));
			glCheck(glBindBuffer(GL_ARRAY_BUFFER, handle));
			glCheck(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
		}

		OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &handle); }

		void OpenGLVertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, handle); }
		void OpenGLVertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
		void OpenGLVertexBuffer::setData(const void* data, size_t size) {
			glBindBuffer(GL_ARRAY_BUFFER, handle);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
		}

		OpenGLIndexBuffer::OpenGLIndexBuffer(uint32* indices, uint32 count): count(count) {
			glCheck(glCreateBuffers(1, &handle));
			glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle));
			glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, GL_STATIC_DRAW));
		}
		OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &handle); }

		uint32 OpenGLIndexBuffer::getCount() const { return count; }

		void OpenGLIndexBuffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle); }
		void OpenGLIndexBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
	}
}
