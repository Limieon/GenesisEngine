#pragma once
#include "GenesisServer/Defines.hpp"

namespace ge {
	namespace server {
		class Chunk;

		class ChunkLayer {
		public:
			ChunkLayer(const ChunkPos2& pos);
			virtual ~ChunkLayer();

			/**
			 * @brief Set a voxel inside a chunk without triggering an update
			 *
			 * @param pos The x, y and z pos
			 * @param voxel The voxel id to set
			 * @param meta The meta of the voxel to set
			 */
			inline void set(uvec3 pos, VoxelI_t voxel, VoxelM_t meta = 0) { set(pos.x, pos.y, pos.z, voxel, meta); }
			/**
			 * @brief Set a voxel inside a chunk without triggering an update
			 *
			 * @param x The x pos
			 * @param y The y pos
			 * @param z The z pos
			 * @param voxel The voxel id to set
			 * @param meta The meta of the voxel to set
			 */
			void set(uint32 x, uint32 y, uint32 z, VoxelI_t voxel, VoxelM_t meta = 0);

			/**
			 * @brief Gets a voxel id
			 *
			 * @param pos The x, y and z pos
			 * @return The voxel id
			 */
			inline VoxelI_t getVoxel(uvec3 pos) const { return getVoxel(pos.x, pos.y, pos.z); }
			/**
			 * @brief Gets a voxel id
			 *
			 * @param x The x pos
			 * @param y The y pos
			 * @param z The z pos
			 * @return The voxel id
			 */
			VoxelI_t getVoxel(uint32 x, uint32 y, uint32 z) const;

			/**
			 * @brief Gets a meta of a voxel
			 *
			 * @param pos The x, y and z pos of the voxel
			 * @return The voxel meta
			 */
			inline VoxelM_t getMeta(uvec3 pos) const { return getMeta(pos.x, pos.y, pos.z); }
			/**
			 * @brief Gets a meta of a voxel
			 *
			 * @param x The x pos
			 * @param y The y pos
			 * @param z The z pos
			 * @return The voxel meta
			 */
			VoxelM_t getMeta(uint32 x, uint32 y, uint32 z) const;

			/**
			 * @brief Gets the position of this chunk layer
			 *
			 * @return The position
			 */
			inline ChunkPos2 getPos() const { return pos; }
			/**
			 * @brief Gets a chunk at a given height
			 *
			 * @param pos The y pos of the chunk
			 * @return The chunk
			 */
			Chunk* getChunk(uint8 pos) const { return chunks[pos]; }

			/**
			 * @brief Reserve chunks in this layer until a specific height
			 *
			 * @param highestPost The highest height of the chunk to reserve (lowest is 0)
			 */
			void reserveChunksUntil(uint8 highestPost);

		private:
			Chunk* chunks[CHUNK_WORLD_HEIGHT] = {nullptr};
			uint8 highestChunkPos = 0;

			ChunkPos2 pos;
		};
	}
}
