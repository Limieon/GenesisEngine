#include "ChunkLayer.hpp"

#include "Chunk.hpp"
#include "World.hpp"

#include <GenesisCore/Logger.hpp>

namespace ge {
	namespace server {
		ChunkLayer::ChunkLayer(World* world, const ChunkPos2& pos): world(world), pos(pos) {}
		ChunkLayer::~ChunkLayer() {
			for(uint8 i = 0; i < highestChunkPos; ++i) {
				delete chunks[i];
			}
		}

		void ChunkLayer::set(uint32 x, uint32 y, uint32 z, VoxelI_t voxel, VoxelM_t meta) {
			GE_Assert(GE_CheckChunkLayerBounds(x, y, z), "Position [{x}, {y}, {z}] is out of bounds!");
			auto chunk = chunks[y / CHUNK_SIZE];
			chunk->set(x, y % CHUNK_SIZE, z, voxel, meta);
		}
		VoxelI_t ChunkLayer::getVoxel(uint32 x, uint32 y, uint32 z) const {
			GE_Assert(GE_CheckChunkLayerBounds(x, y, z), "Position [{x}, {y}, {z}] is out of bounds!");
			return chunks[y / CHUNK_SIZE]->getVoxel(x, y % CHUNK_SIZE, z);
		}
		VoxelM_t ChunkLayer::getMeta(uint32 x, uint32 y, uint32 z) const {
			GE_Assert(GE_CheckChunkLayerBounds(x, y, z), "Position [{x}, {y}, {z}] is out of bounds!");
			return chunks[y / CHUNK_SIZE]->getMeta(x, y % CHUNK_SIZE, z);
		}

		void ChunkLayer::reserveChunksUntil(uint8 highestPos) {
			GE_Assert(highestPos < CHUNK_WORLD_HEIGHT, "Chunk Height {} is out of bounds! (Max: {})", highestPos, (CHUNK_WORLD_HEIGHT - 1));
			if(highestPos <= highestChunkPos) {
				GE_Warn("Requested to reserve chunks until {} but already reserved until {}!", highestPos, highestChunkPos);
				return;
			}

			for(uint8 i = highestChunkPos + 1; i <= highestPos; ++i) {
				chunks[i] = new Chunk(this, i);
			}
			highestChunkPos = highestPos;
		}
	}
}
