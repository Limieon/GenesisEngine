#pragma once
#include "Buffer.hpp"

namespace ge {
	namespace client {
		class IVertexArray {
		public:
			virtual ~IVertexArray() {}

			virtual void bind() const = 0;
			virtual void unbind() const = 0;

			virtual void addVertexBuffer(Ref<IVertexBuffer>& buffer) = 0;
			virtual void setIndexBuffer(Ref<IIndexBuffer>& buffer) = 0;
			virtual Ref<IIndexBuffer> getIndexBuffer() const = 0;

			static Ref<IVertexArray> create();
		};
	}
}
