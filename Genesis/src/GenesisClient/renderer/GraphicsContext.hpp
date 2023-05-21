#pragma once
#include "../Defines.hpp"

namespace ge {
	namespace client {
		class IGraphicsContext {
		public:
			IGraphicsContext() = default;
			virtual ~IGraphicsContext() = default;

			virtual void init() = 0;
			virtual void swapBuffers() = 0;

			static IGraphicsContext* create(void* window);
		};
	}
}
