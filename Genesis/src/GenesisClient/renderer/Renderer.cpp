#include "Renderer.hpp"

#include "Renderer2D.hpp"

namespace ge {
	namespace client {
		void Renderer::init() { Renderer2D::init(); }
		void Renderer::release() { Renderer2D::release(); }
	}
}
