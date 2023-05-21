#include "OpenGLVertexArray.hpp"

#include <glad/glad.h>

namespace ge {
	namespace client {
		static GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type) {
			switch(type) {
				case ShaderDataType::FLOAT: return GL_FLOAT;
				case ShaderDataType::FLOAT2: return GL_FLOAT;
				case ShaderDataType::FLOAT3: return GL_FLOAT;
				case ShaderDataType::FLOAT4: return GL_FLOAT;
				case ShaderDataType::INT: return GL_INT;
				case ShaderDataType::INT2: return GL_INT;
				case ShaderDataType::INT3: return GL_INT;
				case ShaderDataType::INT4: return GL_INT;
				case ShaderDataType::MAT3: return GL_FLOAT;
				case ShaderDataType::MAT4: return GL_FLOAT;
				case ShaderDataType::BOOL: return GL_BOOL;
			}
			return 0;
		}

		OpenGLVertexArray::OpenGLVertexArray() { glCreateVertexArrays(1, &handle); }
		OpenGLVertexArray::~OpenGLVertexArray() { glDeleteVertexArrays(1, &handle); }

		void OpenGLVertexArray::bind() const { glBindVertexArray(handle); }
		void OpenGLVertexArray::unbind() const { glBindVertexArray(0); }

		void OpenGLVertexArray::addVertexBuffer(Ref<IVertexBuffer>& buffer) {
			glBindVertexArray(handle);
			buffer->bind();

			auto layout = buffer->getLayout();

			uint32 i = 0;
			for(const auto& element: layout) {
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, element.getComponentCount(), shaderDataTypeToOpenGLBaseType(element.type),
				                      element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*) element.offset);
				i++;
			}

			vertexBuffers.push_back(buffer);
		}
		void OpenGLVertexArray::setIndexBuffer(Ref<IIndexBuffer>& buffer) {
			glBindVertexArray(handle);
			buffer->bind();
			indexBuffer = buffer;
		}

		Ref<IIndexBuffer> OpenGLVertexArray::getIndexBuffer() const { return indexBuffer; }
	}
}
