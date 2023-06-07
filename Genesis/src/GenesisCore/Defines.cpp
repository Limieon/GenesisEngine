#include "Defines.hpp"
#define GE_Vector2OperatorOverloads_Impl(type)                                                                                                       \
	bool operator==(const type& a, const type& b) { return a.x == b.x && a.y == b.y; }                                                               \
	bool operator!=(const type& a, const type& b) { return a.x != b.x || a.y != b.y; }

#define GE_Vector3OperatorOverloads_Impl(type)                                                                                                       \
	bool operator==(const type& a, const type& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }                                                 \
	bool operator!=(const type& a, const type& b) { return a.x != b.x || a.y != b.y || a.z != b.z; }

GE_Vector3OperatorOverloads_Impl(uvec3);
GE_Vector3OperatorOverloads_Impl(u8vec3);

GE_Vector2OperatorOverloads_Impl(ivec2);
GE_Vector2OperatorOverloads_Impl(i16vec2);

GE_Vector3OperatorOverloads_Impl(ivec3);
