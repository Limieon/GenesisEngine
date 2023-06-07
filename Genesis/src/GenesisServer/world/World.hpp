#pragma once
#include "GenesisServer/Defines.hpp"

namespace ge {
	namespace server {
		class Chunk;
		class ChunkLayer;

		class World {
		public:
			World(const String& id);
			virtual ~World();

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
			 * @brief Gets a chunk at a given height
			 *
			 * @param pos The y pos of the chunk
			 * @return The chunk
			 */
			inline ChunkLayer* getChunk(i16vec2 pos) const;
			/**
			 * @brief Gets a chunk at a given height
			 *
			 * @param x The x pos of the chunk
			 * @param z The z pos of the chunk
			 * @return The chunk
			 */
			inline ChunkLayer* getChunk(int16 x, int16 z) const;

			/**
			 * @brief Gets the world's id
			 *
			 * @return The id
			 */
			inline const String& getID() const { return id; }

			/**
			 * @brief Initializes a new chunk at a given chunk pos
			 *
			 * @param pos The pos of the chunk
			 */
			void initChunk(i16vec2 pos);

		private:
			String id;

			std::unordered_map<i16vec2, ChunkLayer*> chunks;
		};
	}
}
