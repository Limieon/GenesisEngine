#pragma once

/* ---> C++ Standard <--- */
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <format>
#include <functional>
#include <iomanip>
#include <iosfwd>
#include <iterator>
#include <memory>
#include <mutex>
#include <random>
#include <stdlib.h>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/* ---> Streams <--- */
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>

/* ---> GLM <--- */
#include <glm/packing.hpp>
#include <glm/vec3.hpp>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef float float32;
typedef double float64;

typedef std::string String;
typedef uint16 KeyCode;

/// @brief Voxel ID
typedef uint16 VoxelI_t;
/// @brief Voxel Meta
typedef uint8 VoxelM_t;

/* ---> Utiltiy Macros <--- */
/**
 * @brief Create function definitions for operator overloads used for 2d vectors
 *
 */
#define GE_VectorOperatorOverloads(type)                                                                                                             \
	bool operator==(const type& a, const type& b);                                                                                                   \
	bool operator!=(const type& a, const type& b)

/* ---> Voxels / Chunks <--- */
namespace ge {
	/// @brief The axis length in voxels of a single chunk
	constexpr uint32 CHUNK_SIZE = 32;
	/// @brief The height of the entire world, measured in chunks
	constexpr uint32 CHUNK_WORLD_HEIGHT = 32;
	/// @brief To use multiplications instead of divisons for converting block pos to chunk pos
	constexpr float32 ONE_OVER_CHUNK_SIZE = 1.f / CHUNK_SIZE;

	/// @brief The amount of voxels contained in a chunk
	constexpr uint32 CHUNK_VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
	/// @brief The height of the world, measured in voxels
	constexpr uint32 WORLD_HEIGHT = CHUNK_SIZE * CHUNK_WORLD_HEIGHT;

	/// @brief The amount of voxels in a chunk column
	constexpr uint32 CHUNK_LAYER_VOLUME = CHUNK_VOLUME * CHUNK_WORLD_HEIGHT;

	/// @brief The size in bytes of a voxel and it's metadata
	constexpr size_t VOXEL_PAIR_SIZE_BYTES = sizeof(VoxelI_t) + sizeof(VoxelM_t);

	/// @brief The size in bytes of a chunk
	constexpr size_t CHUNK_SIZE_BYTES = CHUNK_VOLUME * VOXEL_PAIR_SIZE_BYTES;
	/// @brief The size in bytes of a chunk column
	constexpr size_t CHUNK_COLUMN_SIZE_BYTES = CHUNK_VOLUME * CHUNK_WORLD_HEIGHT * VOXEL_PAIR_SIZE_BYTES;

	/**
	 * @brief Checks if a coordinate is inside a specific bound
	 *
	 * @tparam T the datatype to check
	 * @param x The x coord
	 * @param y The y coord
	 * @param z The z coord
	 * @param minX Min x (inclusive)
	 * @param minY Min y (inclusive)
	 * @param minZ Min z (inclusive)
	 * @param maxX Max x (exclusive)
	 * @param maxY Max y (exclusive)
	 * @param maxZ Max z (exclusive)
	 * @return true if coordinate is in bound
	 */
	template<typename T>
	static inline bool checkBounds(T x, T y, T z, T minX, T minY, T minZ, T maxX, T maxY, T maxZ) {
		return (x >= minX && x < maxX) && (y >= minY && y < maxY) && (z >= minZ && z < maxZ);
	}
	/**
	 * @brief Checks if a coordinate is inside a specific bound
	 *
	 * @tparam T the datatype to check
	 * @param x The x coord
	 * @param y The y coord
	 * @param z The z coord
	 * @param size The size of the bound (maxX, maxY and maxZ exclusive)
	 * @return true if coordinate is in bound
	 */
	template<typename T>
	static inline bool checkBounds(T x, T y, T z, T size) {
		return checkBounds<T>(x, y, z, 0, 0, 0, size, size, size);
	}
}

#define GE_CheckChunkBounds(x, y, z) (x >= 0 && x < ge::CHUNK_SIZE) && (y >= 0 && y < ge::CHUNK_SIZE) && (z >= 0 && z < ge::CHUNK_SIZE)
#define GE_CheckChunkLayerBounds(x, y, z) (x >= 0 && x < ge::CHUNK_SIZE) && y >= 0 && (y < ge::WORLD_HEIGHT) && (z >= 0 && z < ge::CHUNK_SIZE)

/* ---> Vectors <--- */
typedef glm::vec<3, uint32, glm::defaultp> uvec3;
typedef glm::vec<3, uint8, glm::defaultp> u8vec3;
typedef glm::vec<2, int32, glm::defaultp> ivec2;
typedef glm::vec<2, int16, glm::defaultp> i16vec2;

typedef glm::ivec3 ivec3;

/* ---> Operator Overloads for those vectors */
GE_VectorOperatorOverloads(uvec3);
GE_VectorOperatorOverloads(u8vec3);

GE_VectorOperatorOverloads(ivec2);
GE_VectorOperatorOverloads(i16vec2);

GE_VectorOperatorOverloads(ivec3);

/* ---> Poisitions <--- */
namespace ge {
	struct ChunkPos2 {
		ChunkPos2(int16 x, int16 y): x(x), z(z) {}
		ChunkPos2(const i16vec2& vec): x(vec.x), z(vec.y) {}

		inline i16vec2 toI16Vec2() const { return i16vec2(x, z); }
		inline operator i16vec2() const { return toI16Vec2(); }

		int16 x, z;
	};

	struct ChunkPos3 {
		ChunkPos3(ChunkPos2 pos, uint8 y): pos(pos), y(y) {}

		static ChunkPos2 asChunkPos2(ChunkPos3 pos) { return pos.pos; }

		ChunkPos2 pos;
		uint8 y;
	};
}

/* ---> Util Macros <--- */
#define GE_BIT(x) (1 << x)

// Returns the smaller values of the two
// WARNING: Macro based, can produce errors
#define GE_Min(left, right) left > right ? right : left
// Returns the greater values of the two
// WARNING: Macro based, can produce errors
#define GE_Max(left, right) left < right ? right : left
// Returns max if the value is bigger than max, min if the value is less than min, value if the value is between min and max
// WARNING: Macro based, can produce errors
#define GE_Clamp(value, min, max) (value > max) ? max : (value < min) ? min : value

// Bind a event function
#define GE_BindEventFunction(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

/* ---> Memory <--- */
template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename... Args>
constexpr Scope<T> createScope(Args&&... args) {
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename... Args>
constexpr Ref<T> createRef(Args&&... args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}

// Combines certain values to hashes together
inline void hash_combine(std::size_t& seed) {}
template<typename T, typename... Rest>
inline void hash_combine(std::size_t& seed, const T& v, Rest... rest) {
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	hash_combine(seed, rest...);
}

// Makes a class hashable (fields have to start with t.)
#define GE_MakeHashable(type, ...)                                                                                                                   \
	namespace std {                                                                                                                                  \
		template<>                                                                                                                                   \
		struct hash<type> {                                                                                                                          \
			std::size_t operator()(const type& t) const {                                                                                            \
				std::size_t ret = 0;                                                                                                                 \
				hash_combine(ret, __VA_ARGS__);                                                                                                      \
				return ret;                                                                                                                          \
			}                                                                                                                                        \
		};                                                                                                                                           \
	}

// Create hash functions for the common types used in maps
namespace std {
	template<>
	struct hash<i16vec2> {
		std::size_t operator()(const i16vec2& t) const { return (t.x << 16) | t.y; }
	};
}
