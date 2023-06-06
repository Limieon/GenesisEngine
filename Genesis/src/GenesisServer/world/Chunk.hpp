#pragma once
#include <GenesisServer/Defines.hpp>

namespace ge {
	namespace server {
		class ChunkLayer;

		class Chunk {
		public:
			Chunk(ChunkLayer* layer, uint8 pos);
			virtual ~Chunk();

			inline void set(u8vec3 pos, VoxelI_t voxel, VoxelM_t meta = 0) { set(pos.x, pos.y, pos.z, voxel, meta); }
			void set(uint8 x, uint8 y, uint8 z, VoxelI_t voxel, VoxelM_t meta = 0);

			inline VoxelI_t getVoxel(u8vec3 pos) const { return getVoxel(pos.x, pos.y, pos.z); }
			VoxelI_t getVoxel(uint8 x, uint8 y, uint8 z) const;

			inline VoxelM_t getMeta(u8vec3 pos) const { return getMeta(pos.x, pos.y, pos.z); }
			VoxelM_t getMeta(uint8 x, uint8 y, uint8 z) const;

			ChunkPos3 getPos() const;

			inline ChunkLayer* getLayer() const { return layer; }

		private:
			VoxelI_t voxels[ge::CHUNK_SIZE][ge::CHUNK_SIZE][ge::CHUNK_SIZE] = {0};
			VoxelM_t metas[ge::CHUNK_SIZE][ge::CHUNK_SIZE][ge::CHUNK_SIZE] = {0};

			/// @brief The vertical pos of the chunk
			uint8 pos;
			/// @brief The chunk layer, the chunk is in
			ChunkLayer* layer;
		};
	}
}
