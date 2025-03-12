/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -VectorMath.hpp-
 *  Basic vector formulas for vec2, vec3, and vec4
 */

#pragma once

#include <Core/Types/BasicTypes.hpp>

namespace core::math
{

template<typename T>
inline float length(vec2<T> value)
{
    return std::sqrt(value.x * value.x + value.y * value.y);
}

template<typename T>
inline float length(vec3<T> value)
{
    return std::sqrt(
        value.x * value.x + value.y * value.y + value.z * value.z);
}

template<typename T>
inline float length(vec4<T> value)
{
    return std::sqrt(
        value.x * value.x + value.y * value.y + value.z * value.z + value.w * value.w);    
}

template<typename T>
vec2<T> normalize2(vec2<T> value)
{
    float len = core::math::length<T>(value);
    if (len == 0.0f) len = 1.0f;

    float val = 1.0f / len;
    return vec2<T>(value.x * val, value.y * val);
}

template<typename T>
vec3<T> normalize3(vec3<T> value)
{
    float len = core::math::length<T>(value);
    if (len == 0.0f) len = 1.0f;

    len = 1.0f / len;
    return vec3<T>(value.x * len, value.y * len, value.z * len);
}

template<typename T>
vec4<T> normalize4(vec4<T> value)
{
    float len = core::math::length<T>(value);
    if (len == 0.0f) len = 1.0f;

    float val = 1.0f / len;
    return vec4<T>(value.x * val, value.y * val, value.z * val, value.w * val);    
}

template<typename T>
vec3<T> cross3(vec3<T> v1, vec3<T> v2)
{
	return vec3<T>(
		v1.y * v2.z - v1.z * v2.y, v1.z * v2.x 
	  - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

template<typename T>
f32 distance(vec3<T> v1, vec3<T> v2)
{
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    float dz = v2.z - v1.z;
    float result = std::sqrt(dx*dx + dy*dy + dz*dz);
    return result;
}

}