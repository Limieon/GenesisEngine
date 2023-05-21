#pragma once
#include "GenesisClient/Platform.hpp"

namespace ge {
	namespace client {
		class WindowsPlatform: public Platform {
		public:
			float32 getTimeImpl() const override;
		};
	}
}
