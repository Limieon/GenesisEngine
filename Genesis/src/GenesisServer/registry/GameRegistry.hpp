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

			inline static VoxelI_t getVoxelID(const String& unlocalizedName);
			inline static const String& getUnlocalizedName(VoxelI_t id);

			inline static const Voxel& getVoxel(const String& unlocalizedName);
			inline static const Voxel& getVoxel(VoxelI_t id);

		public:
			static void debugPrintData();

		private:
			static GameRegistry::VoxelData* vData;
		};
	}
}
