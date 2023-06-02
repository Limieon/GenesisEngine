#pragma once
#include "GenesisServer/Defines.hpp"
#include "GenesisServer/voxel/Voxel.hpp"

namespace ge {
	namespace server {
		class GameRegistry {
		public:
			using VoxelIDMap = std::unordered_map<String, VoxelI_t>;
			using VoxelArray = std::vector<const Voxel*>;

			struct VoxelData {
				VoxelIDMap map;
				VoxelArray array;
			};

		public:
			static void init();
			static void release();

			static void registerVoxel(const Voxel* voxel);

			static inline VoxelI_t getVoxelID(const String& unlocalizedName) { return vData->map[unlocalizedName]; }
			static inline const String& getUnlocalizedName(VoxelI_t id) { return vData->array[id]->getUnlocalizedName(); }

			static inline const Voxel& getVoxel(const String& unlocalizedName) { return *vData->array[getVoxelID(unlocalizedName)]; }
			static inline const Voxel& getVoxel(VoxelI_t id) { return *vData->array[id]; }

		public:
			static void debugPrintData();

		private:
			static GameRegistry::VoxelData* vData;
		};
	}
}
