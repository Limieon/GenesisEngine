#include "World.hpp"

#include "Chunk.hpp"
#include "ChunkLayer.hpp"

namespace ge {
	namespace server {
		World::World(const String& id): id(id) {}
		World::~World() {
			for(auto it = chunks.begin(); it != chunks.end(); ++it) {
				delete it->second;
			}
		}

		void World::set(uint32 x, uint32 y, uint32 z, VoxelI_t voxel, VoxelM_t meta) {
			getChunk(i16vec2(x * ONE_OVER_CHUNK_SIZE, z * ONE_OVER_CHUNK_SIZE))->set(x % CHUNK_SIZE, y, z % CHUNK_SIZE, voxel, meta);
		}

		VoxelI_t World::getVoxel(uint32 x, uint32 y, uint32 z) const {
			return getChunk(i16vec2(x * ONE_OVER_CHUNK_SIZE, z * ONE_OVER_CHUNK_SIZE))->getVoxel(x % CHUNK_SIZE, y, z % CHUNK_SIZE);
		}
		VoxelM_t World::getMeta(uint32 x, uint32 y, uint32 z) const {
			return getChunk(i16vec2(x * ONE_OVER_CHUNK_SIZE, z * ONE_OVER_CHUNK_SIZE))->getMeta(x % CHUNK_SIZE, y, z % CHUNK_SIZE);
		}

		ChunkLayer* World::getChunk(i16vec2 pos) const { return chunks.at(pos); }
		ChunkLayer* World::getChunk(int16 x, int16 z) const { return chunks.at(i16vec2(x, z)); }

		void World::initChunk(i16vec2 pos) { chunks[pos] = new ChunkLayer(this, pos); }
	}
}
