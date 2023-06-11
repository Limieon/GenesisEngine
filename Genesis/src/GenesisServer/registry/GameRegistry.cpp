#include "GameRegistry.hpp"

#include "GenesisCore/Logger.hpp"

namespace ge {
	namespace server {
		GameRegistry::VoxelData GameRegistry::vData = GameRegistry::VoxelData {};

		void GameRegistry::init() {}
		void GameRegistry::release() {
			for(Voxel* voxel: vData.array) {
				delete voxel;
			}
			vData.array.clear();
		}

		void GameRegistry::registerVoxel(Voxel* voxel) {
			VoxelI_t index = vData.array.size();
			vData.array.push_back(voxel);
			vData.map.insert(std::pair<std::string, VoxelI_t>(voxel->getUnlocalizedName(), index));
		}

		void GameRegistry::debugPrintData() {
			GE_Info("Currently there are {} voxels registered!", vData.array.size());
			for(auto it = vData.map.begin(); it != vData.map.end(); ++it) {
				GE_Info("Voxel '{}' with id: {}", it->first, it->second);
			}
		}
	}
}
