/**
  Open Simple Noise for C++
  Port to C++ from https://gist.github.com/KdotJPG/b1270127455a94ac5d19
  by Rickard Lundberg, 2019.
*/

#pragma once

#include "Core/Types/NumberTypes.hpp"
#include <array>

namespace core
{

class SimplexNoise
{
public:
    SimplexNoise();
    SimplexNoise(long long seed);

    //2D Open Simplex Noise.
    [[nodiscard]] double eval(f64 x, f64 y) const;
    //3D Open Simplex Noise.
    [[nodiscard]] double eval(f64 x, f64 y, f64 z) const;
    //4D Open Simplex Noise.
    [[nodiscard]] double eval(f64 x, f64 y, f64 z, f64 w) const;
private:
    const double m_stretch2d;
    const double m_squish2d;
    const double m_stretch3d;
    const double m_squish3d;
    const double m_stretch4d;
    const double m_squish4d;

    const double m_norm2d;
    const double m_norm3d;
    const double m_norm4d;

    const long m_defaultSeed;

    std::array<short, 256> m_perm;
    std::array<short, 256> m_permGradIndex3d;
    std::array<char, 16> m_gradients2d;
    std::array<char, 72> m_gradients3d;
    std::array<char, 256> m_gradients4d;
    double extrapolate(s32 xsb, s32 ysb, f64 dx, f64 dy) const;
    double extrapolate(s32 xsb, s32 ysb, s32 zsb, f64 dx, f64 dy, f64 dz) const;
    double extrapolate(s32 xsb, s32 ysb, s32 zsb, s32 wsb, f64 dx, f64 dy, f64 dz, f64 dw) const;
};
}