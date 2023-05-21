#pragma once
#include "GenesisClient/Defines.hpp"

namespace ge {
	namespace client {
		class Platform {
		public:
			inline static float32 getTime() { return instance->getTimeImpl(); }

		public:
			virtual float32 getTimeImpl() const = 0;

		private:
			static Platform* instance;
		};
	}
}
