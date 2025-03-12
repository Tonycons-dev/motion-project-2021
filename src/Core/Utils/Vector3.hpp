/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -Vector3.hpp-
 *      Three-dimensional vector with arithmetic functions
 *      (scalar and vector addition, subtraction, multiplication, division).
 */

#ifndef _CORE_VECTOR3_
#define _CORE_VECTOR3_

namespace core {

template<typename T>
struct vec3
{
public:
    T x, y, z;

    vec3() noexcept: x(0), y(0),z(0){}

    vec3(const vec3<T>& v) noexcept:
        x(v.x), y(v.y), z(v.z){}

    template<typename U>
    explicit vec3(const vec3<U>& v):
        x(static_cast<T>(v.x)),
        y(static_cast<T>(v.y)),
        z(static_cast<T>(v.z)){}  

    explicit vec3(T s) noexcept: x(s), y(s), z(s) {}
    vec3(T x, T y, T z) noexcept:
        x(x), y(y), z(z){}

    bool isWithinRange(T _min, T _max) noexcept
    {
        return 
        x > _min && x < _max &&
        y > _min && y < _max &&
        z > _min && z < _max;
    }

    T& operator[](unsigned int index)
    {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        return x;
    }

    const T& operator[](unsigned int index) const
    {
        if (index == 0) return x;
        if (index == 1) return y;
        if (index == 2) return z;
        return x;
    }
};

#ifdef VECTOR_INLINE
#define VECTOR_DECL inline
#else
#define VECTOR_DECL
#endif

#define VECTOR3_ARITHMETIC_DEF(op, compoundOp)                                  \
                                                                                \
template<typename T>                                                            \
VECTOR_DECL vec3<T> operator op (const vec3<T>& left, const vec3<T>& right)     \
noexcept                                                                        \
{                                                                               \
    return vec3<T>(                                                             \
        left.x op right.x,                                                      \
        left.y op right.y,                                                      \
        left.z op right.z);                                                     \
}                                                                               \
                                                                                \
template<typename T>                                                            \
VECTOR_DECL vec3<T> operator op (const vec3<T>& left, T right)                  \
noexcept                                                                        \
{                                                                               \
    return vec3<T>(                                                             \
        left.x op right,                                                        \
        left.y op right,                                                        \
        left.z op right);                                                       \
}                                                                               \
                                                                                \
template<typename T, typename U>                                                \
VECTOR_DECL vec3<T> operator op (const vec3<T>& left, U right)                  \
noexcept                                                                        \
{                                                                               \
    return vec3<T>(                                                             \
        left.x op static_cast<T>(right),                                        \
        left.y op static_cast<T>(right),                                        \
        left.z op static_cast<T>(right));                                       \
}                                                                               \
                                                                                \
template<typename T, typename U>                                                \
VECTOR_DECL vec3<T> operator op (const vec3<T>& left, const vec3<U>& right)     \
noexcept                                                                        \
{                                                                               \
    return vec3<T>(                                                             \
        left.x op static_cast<T>(right.x),                                      \
        left.y op static_cast<T>(right.y),                                      \
        left.z op static_cast<T>(right.z));                                     \
}                                                                               \
                                                                                \
template<typename T>                                                            \
VECTOR_DECL vec3<T>& operator compoundOp (vec3<T>& left, const vec3<T>& right)  \
noexcept                                                                        \
{                                                                               \
    left.x compoundOp right.x;                                                  \
    left.y compoundOp right.y;                                                  \
    left.z compoundOp right.z;                                                  \
    return left;                                                                \
}                                                                               \
                                                                                \
template<typename T, typename U>                                                \
VECTOR_DECL vec3<T>& operator compoundOp (vec3<T>& left, const vec3<U>& right)  \
noexcept                                                                        \
{                                                                               \
    left.x compoundOp static_cast<T>(right.x);                                  \
    left.y compoundOp static_cast<T>(right.y);                                  \
    left.z compoundOp static_cast<T>(right.z);                                  \
    return left;                                                                \
}                                                                               \
                                                                                \
template<typename T>                                                            \
VECTOR_DECL vec3<T>& operator compoundOp (vec3<T>& left, T right)               \
noexcept                                                                        \
{                                                                               \
    left.x compoundOp right;                                                    \
    left.y compoundOp right;                                                    \
    left.z compoundOp right;                                                    \
    return left;                                                                \
}                                                                               \
                                                                                \
template<typename T, typename U>                                                \
VECTOR_DECL vec3<T>& operator compoundOp (vec3<T>& left, U right)               \
noexcept                                                                        \
{                                                                               \
    left.x compoundOp static_cast<T>(right);                                    \
    left.y compoundOp static_cast<T>(right);                                    \
    left.z compoundOp static_cast<T>(right);                                    \
    return left;                                                                \
}                                                                               \

VECTOR3_ARITHMETIC_DEF(+, +=)
VECTOR3_ARITHMETIC_DEF(-, -=)
VECTOR3_ARITHMETIC_DEF(*, *=)
VECTOR3_ARITHMETIC_DEF(/, /=)


template<typename T>
VECTOR_DECL vec3<T> operator-(const vec3<T> v)
noexcept
{
    return vec3<T>(-v.x, -v.y, -v.z);
}

//template <typename T>
//VECTOR_DECL vec3<T> operator*(T left, const vec3<T>& right)
//{
//    return vec3<T>(
//    right.x * left, right.y * left, right.z * left);
//}
//
//template<typename T, typename U>
//VECTOR_DECL vec3<T> operator*(U _left, const vec3<T>& right)
//{
//    const T left = static_cast<T>(_left);
//    return vec3<T>(right.x * left, right.y * left, right.z * left);
//}

template<typename T>
VECTOR_DECL bool operator> (const vec3<T>& left, const vec3<T>& right)
noexcept {
    return (left.x > right.x)
        && (left.y > right.y) && (left.z > right.z);
}

template<typename T>
VECTOR_DECL bool operator< (const vec3<T>& left, const vec3<T>& right)
noexcept {
    return (left.x < right.x)
       && (left.y < right.y) && (left.z < right.z);
}

template<typename T>
VECTOR_DECL bool operator>=(const vec3<T>& left, const vec3<T>& right)
noexcept {
    return (left.x >= right.x)
       && (left.y >= right.y) && (left.z >= right.z);
}

template<typename T>
VECTOR_DECL bool operator<=(const vec3<T>& left, const vec3<T>& right)
noexcept {
    return (left.x <= right.x)
       && (left.y <= right.y) && (left.z <= right.z);
}

template <typename T>
VECTOR_DECL bool operator==(const vec3<T>& left, const vec3<T>& right)
noexcept
{
    return
    (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

template <typename T>
VECTOR_DECL bool operator!=(const vec3<T>& left, const vec3<T>& right)
noexcept
{
    return 
    (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}

template <typename T, typename U>
bool operator!=(const vec3<T>& left, const vec3<U>& right) noexcept
{
    #if __cplusplus >= 201700L
    if constexpr (sizeof(T) >= sizeof(U))
    #else
    if (sizeof(T) >= sizeof(U))
    #endif
    {
        return
        (left.x != static_cast<T>(right.x)) && (left.y != static_cast<T>(right.y)) &&
        (left.z != static_cast<T>(right.z));
    }
    #if __cplusplus >= 201700L
    else if constexpr (sizeof(T) < sizeof(U))
    #else
    else if (sizeof(T) < sizeof(U))
    #endif
    {
        return
        (static_cast<U>(left.x) != right.x) && (static_cast<U>(left.y) != right.y) &&
        (static_cast<U>(left.z) != right.z);
    }
}

template <typename T, typename U>
bool operator==(const vec3<T>& left, const vec3<U>& right) noexcept
{
    #if __cplusplus >= 201700L
    if constexpr (sizeof(T) >= sizeof(U))
    #else
    if (sizeof(T) >= sizeof(U))
    #endif
    {
        return
        (left.x == static_cast<T>(right.x)) && (left.y == static_cast<T>(right.y)) &&
        (left.z == static_cast<T>(right.z));
    }
    #if __cplusplus >= 201700L
    else if constexpr (sizeof(T) < sizeof(U))
    #else
    else if (sizeof(T) < sizeof(U))
    #endif
    {
        return
        (static_cast<U>(left.x) == right.x) && (static_cast<U>(left.y) == right.y) &&
        (static_cast<U>(left.z) == right.z);
    }
}
}

using vec3b = core::vec3<unsigned char>;
using vec3c = core::vec3<char>;
using vec3u = core::vec3<unsigned int>;
using vec3i = core::vec3<int>;
using vec3f = core::vec3<float>;
using vec3d = core::vec3<double>;
#endif