#include "GameRegistry.hpp"

#include "GenesisCore/Logger.hpp"

namespace ge {
	namespace server {
		GameRegistry::VoxelData* GameRegistry::vData = nullptr;

		void GameRegistry::init() { vData = new VoxelData; }
		void GameRegistry::release() { delete vData; }

		void GameRegistry::registerVoxel(const Voxel* voxel) {
			VoxelI_t index = vData->array.size();
			vData->array.push_back(voxel);
			vData->map.insert(std::pair<const String&, uint32>(voxel->getUnlocalizedName(), index));
		}

		VoxelI_t GameRegistry::getVoxelID(const String& unlocalizedName) { return vData->map[unlocalizedName]; }
		const String& GameRegistry::getUnlocalizedName(VoxelI_t id) { return vData->array[id]->getUnlocalizedName(); }

		const Voxel& GameRegistry::getVoxel(const String& unlocalizedName) { return *vData->array[getVoxelID(unlocalizedName)]; }
		const Voxel& GameRegistry::getVoxel(VoxelI_t id) { return *vData->array[id]; }

		void GameRegistry::debugPrintData() {
			GE_Info("Currently there are {} voxels registered!", vData->array.size());
			for(auto it = vData->map.begin(); it != vData->map.end(); ++it) {
				GE_Info("Voxel '{}' with id: {}", it->first, it->second);
			}
		}
	}
}
