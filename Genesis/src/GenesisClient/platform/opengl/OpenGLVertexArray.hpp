#pragma once
#include "GenesisClient/renderer/Buffer.hpp"
#include "GenesisClient/renderer/VertexArray.hpp"

namespace ge {
	namespace client {
		class OpenGLVertexArray: public IVertexArray {
		public:
			OpenGLVertexArray();
			virtual ~OpenGLVertexArray();

			virtual void bind() const override;
			virtual void unbind() const override;

			virtual void addVertexBuffer(Ref<IVertexBuffer>& buffer) override;
			virtual void setIndexBuffer(Ref<IIndexBuffer>& buffer) override;
			virtual Ref<IIndexBuffer> getIndexBuffer() const override;

		private:
			uint32 handle;
			Ref<IIndexBuffer> indexBuffer;
			std::vector<Ref<IVertexBuffer>> vertexBuffers;
		};
	}
}
