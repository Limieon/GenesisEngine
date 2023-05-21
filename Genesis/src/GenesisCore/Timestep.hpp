#pragma once
#include "Defines.hpp"

namespace ge {
	namespace core {
		class Timestep {
		public:
			Timestep(float32 time = 0.f): time(time) {}

			operator float32() const { return time; }

			float32 getSeconds() const { return time; }
			float32 getMilliseconds() const { return time * 1000.f; }

		private:
			float32 time;
		};
	}
}
