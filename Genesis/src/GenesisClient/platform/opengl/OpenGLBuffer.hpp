#pragma once
#include "GenesisClient/renderer/Buffer.hpp"

namespace ge {
	namespace client {
		class OpenGLVertexBuffer: public IVertexBuffer {
		public:
			OpenGLVertexBuffer(size_t size);
			OpenGLVertexBuffer(const void* data, size_t size);
			virtual ~OpenGLVertexBuffer();

			void setLayout(const BufferLayout& layout) { this->layout = layout; }
			const BufferLayout& getLayout() const override { return layout; }

			void bind() const override;
			void unbind() const override;
			void setData(const void* data, size_t size) override;

		private:
			uint32 handle;
			BufferLayout layout;
		};

		class OpenGLIndexBuffer: public IIndexBuffer {
		public:
			OpenGLIndexBuffer(uint32* indices, uint32 count);
			virtual ~OpenGLIndexBuffer();

			void bind() const override;
			void unbind() const override;

			uint32 getCount() const override;

		private:
			uint32 handle;
			uint32 count;
		};
	}
}
