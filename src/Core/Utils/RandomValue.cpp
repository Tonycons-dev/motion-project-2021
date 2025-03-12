/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -RandomValue.hpp-
 *      Basic functions to obtain randomized values.
 */

#include "Core/Utils/RandomValue.hpp"
#include <random>

s32 core::getRandomInt(s32 minimum, s32 maximum)
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::uniform_int_distribution<> dist(minimum, maximum);
    return dist(generator);
}

f32 core::getRandomFloat(f32 minimum, f32 maximum)
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::uniform_real_distribution<> dist(
        static_cast<double>(minimum), static_cast<double>(maximum));

    return static_cast<float>(dist(generator));
}

f64 core::getRandomDouble(f64 minimum, f64 maximum)
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::uniform_real_distribution<> dist(minimum, maximum);
    return dist(generator);
}

void core::getRandomIntArray(s32 minimum, s32 maximum, s32 *data, u32 size)
{
    if (data == nullptr || size == 0)
        return;

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::uniform_int_distribution<> dist(minimum, maximum);

    for (u32 i = 0; i < size; i++)
        data[i] = dist(generator);
}

void core::getRandomFloatArray(f32 minimum, f32 maximum, f32 *data, u32 size)
{
    if (data == nullptr || size == 0)
        return;

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::uniform_real_distribution<> dist(
        static_cast<double>(minimum), static_cast<double>(maximum));

    for (u32 i = 0; i < size; i++)
        data[i] = static_cast<float>(dist(generator));
}

void core::getRandomDoubleArray(f64 minimum, f64 maximum, f64 *data, u32 size)
{
    if (data == nullptr || size == 0)
        return;

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());

    std::uniform_real_distribution<> dist(minimum, maximum);

    for (u32 i = 0; i < size; i++)
        data[i] = dist(generator);
}