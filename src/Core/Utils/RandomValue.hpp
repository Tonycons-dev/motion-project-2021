/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -RandomValue.hpp-
 *      Basic functions to obtain randomized values.
 */

#pragma once
#include "Core/Types/BasicTypes.hpp"

namespace core
{
    f32 getRandomFloat(f32 minimum, f32 maximum);
    s32 getRandomInt(s32 minimum, s32 maximum);
    f64 getRandomDouble(f64 minimum, f64 maximum);

    void getRandomFloatArray(f32 minimum, f32 maximum, f32* data, u32 size);
    void getRandomIntArray(s32 minimum, s32 maximum, s32* data, u32 size);
    void getRandomDoubleArray(f64 minimum, f64 maximum, f64* data, u32 size);
}