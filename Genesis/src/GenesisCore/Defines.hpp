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
typedef uint32 VoxelI_t;
/// @brief Voxel Meta Data
typedef uint32 VoxelM_t;

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
template<typename T> using Scope = std::unique_ptr<T>;
template<typename T, typename... Args> constexpr Scope<T> createScope(Args&&... args) { return std::make_unique<T>(std::forward<Args>(args)...); }

template<typename T> using Ref = std::shared_ptr<T>;
template<typename T, typename... Args> constexpr Ref<T> createRef(Args&&... args) { return std::make_shared<T>(std::forward<Args>(args)...); }
