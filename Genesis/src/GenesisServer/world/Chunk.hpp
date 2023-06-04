#pragma once
#include <GenesisServer/Defines.hpp>

namespace ge {
	namespace server {
		class Chunk {
		public:
			Chunk();
			virtual ~Chunk();

			inline void set(u8vec3 pos, VoxelI_t voxel, VoxelM_t meta = 0) { set(pos.x, pos.y, pos.z, voxel, meta); }
			void set(uint8 x, uint8 y, uint8 z, VoxelI_t voxel, VoxelM_t meta = 0);

			inline VoxelI_t getVoxel(u8vec3 pos, VoxelI_t voxel) const { return getVoxel(pos.x, pos.y, pos.z); }
			VoxelI_t getVoxel(uint8 x, uint8 y, uint8 z) const;

			inline VoxelM_t getMeta(u8vec3 pos, VoxelI_t voxel) const { return getMeta(pos.x, pos.y, pos.z); }
			VoxelM_t getMeta(uint8 x, uint8 y, uint8 z) const;

		private:
			VoxelI_t voxels[ge::CHUNK_SIZE][ge::CHUNK_SIZE][ge::CHUNK_SIZE] = {0};
			VoxelM_t metas[ge::CHUNK_SIZE][ge::CHUNK_SIZE][ge::CHUNK_SIZE] = {0};
		};
	}
}
