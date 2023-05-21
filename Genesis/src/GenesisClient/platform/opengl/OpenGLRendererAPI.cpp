#include "OpenGLRendererAPI.hpp"

#include <glad/glad.h>

namespace ge {
	namespace client {
		void OpenGLRendererAPI::init() {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glEnable(GL_DEPTH_TEST);
		}

		void OpenGLRendererAPI::drawIndexed(const Ref<IVertexArray>& arr, uint32 indexCount) {
			arr->bind();
			glDrawElements(GL_TRIANGLES, indexCount ? indexCount : arr->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
		}
		void OpenGLRendererAPI::setClearColor(const glm::vec4& color) { glClearColor(color.r, color.g, color.b, color.a); }
		void OpenGLRendererAPI::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

		void OpenGLRendererAPI::setViewport(uint32 x, uint32 y, uint32 width, uint32 height) { glViewport(x, y, width, height); }
	}
}
