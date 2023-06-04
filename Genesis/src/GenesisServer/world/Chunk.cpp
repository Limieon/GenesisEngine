#include "Chunk.hpp"

#include <GenesisCore/Logger.hpp>

namespace ge {
	namespace server {
		Chunk::Chunk() {}
		Chunk::~Chunk() {}

		void Chunk::set(uint8 x, uint8 y, uint8 z, VoxelI_t voxel, VoxelM_t meta) {
			GE_Assert(GE_CheckChunkBounds(x, y, z), "Position [{x}, {y}, {z}] is out of bounds!");
			voxels[x][y][z] = voxel;
			metas[x][y][z] = meta;
		}
		VoxelI_t Chunk::getVoxel(uint8 x, uint8 y, uint8 z) const {
			GE_Assert(GE_CheckChunkBounds(x, y, z), "Position [{x}, {y}, {z}] is out of bounds!");
			return voxels[x][y][z];
		}
		VoxelM_t Chunk::getMeta(uint8 x, uint8 y, uint8 z) const {
			GE_Assert(GE_CheckChunkBounds(x, y, z), "Position [{x}, {y}, {z}] is out of bounds!");
			return metas[x][y][z];
		}
	}
}
