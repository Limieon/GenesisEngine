#pragma once
#include "GenesisServer/Defines.hpp"

namespace ge {
	namespace server {
		class Voxel {
		public:
			Voxel(const String& unlocalizedName);
			virtual ~Voxel();

			inline String getUnlocalizedName() const { return unlocalizedName; }

		private:
			String unlocalizedName;
		};
	}
}
