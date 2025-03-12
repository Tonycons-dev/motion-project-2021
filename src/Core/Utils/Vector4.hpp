/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -Vector4.hpp-
 *      Four-dimensional vector with arithmetic functions
 *      (scalar and vector addition, subtraction, multiplication, division).
 */

#ifndef _CORE_VECTOR4_
#define _CORE_VECTOR4_

namespace core {

template<typename T>
struct vec4
{
public:
    T x, y, z, w;

    vec4() noexcept: x(0), y(0), z(0), w(0){}
    vec4(const vec4<T>& v) noexcept: x(v.x), y(v.y), z(v.z), w(v.w){}

    template<typename U>
    explicit vec4(const vec4<U>& v):
        x(static_cast<T>(v.x)), y(static_cast<T>(v.y)),
        z(static_cast<T>(v.z)), w(static_cast<T>(v.w)){}  

    explicit vec4(T s) noexcept: x(s), y(s), z(s), w(s) {}
    vec4(T x, T y, T z, T w) noexcept: x(x), y(y), z(z), w(w){}

    bool isWithinRange(T _min, T _max)
    {
        return 
        x > _min && x < _max && y > _min && y < _max &&
        z > _min && z < _max && w > _min && z < _max;
    }
};

#ifdef VECTOR_INLINE
#define VECTOR_DECL inline
#else
#define VECTOR_DECL
#endif

#define VECTOR4_ARITHMETIC_DEF(op, compoundOp)                                  \
                                                                                \
template<typename T>                                                            \
VECTOR_DECL vec4<T> operator op (const vec4<T>& left, const vec4<T>& right)     \
noexcept                                                                        \
{                                                                               \
    return vec4<T>(                                                             \
        left.x op right.x,                                                      \
        left.y op right.y,                                                      \
        left.z op right.z,                                                      \
        left.w op right.w);                                                     \
}                                                                               \
                                                                                \
template<typename T>                                                            \
VECTOR_DECL vec4<T> operator op (const vec4<T>& left, T right)                  \
noexcept                                                                        \
{                                                                               \
    return vec4<T>(                                                             \
        left.x op right,                                                        \
        left.y op right,                                                        \
        left.z op right,                                                        \
        left.w op right);                                                       \
}                                                                               \
                                                                                \
template<typename T, typename U>                                                \
VECTOR_DECL vec4<T> operator op (const vec4<T>& left, U right)                  \
noexcept                                                                        \
{                                                                               \
    return vec4<T>(                                                             \
        left.x op static_cast<T>(right),                                        \
        left.y op static_cast<T>(right),                                        \
        left.z op static_cast<T>(right),                                        \
        left.w op static_cast<T>(right));                                       \
}                                                                               \
                                                                                \
template<typename T, typename U>                                                \
VECTOR_DECL vec4<T> operator op (const vec4<T>& left, const vec4<U>& right)     \
noexcept                                                                        \
{                                                                               \
    return vec4<T>(                                                             \
        left.x op static_cast<T>(right.x),                                      \
        left.y op static_cast<T>(right.y),                                      \
        left.z op static_cast<T>(right.z),                                      \
        left.w op static_cast<T>(right.w));                                     \
}                                                                               \
                                                                                \
template<typename T>                                                            \
VECTOR_DECL vec4<T>& operator compoundOp (vec4<T>& left, const vec4<T>& right)  \
noexcept                                                                        \
{                                                                               \
    left.x compoundOp right.x;                                                  \
    left.y compoundOp right.y;                                                  \
    left.z compoundOp right.z;                                                  \
    left.w compoundOp right.w;                                                  \
    return left;                                                                \
}                                                                               \
                                                                                \
template<typename T, typename U>                                                \
VECTOR_DECL vec4<T>& operator compoundOp (vec4<T>& left, const vec4<U>& right)  \
noexcept                                                                        \
{                                                                               \
    left.x compoundOp static_cast<T>(right.x);                                  \
    left.y compoundOp static_cast<T>(right.y);                                  \
    left.z compoundOp static_cast<T>(right.z);                                  \
    left.w compoundOp static_cast<T>(right.w);                                  \
    return left;                                                                \
}                                                                               \
                                                                                \
template<typename T>                                                            \
VECTOR_DECL vec4<T>& operator compoundOp (vec4<T>& left, T right)               \
noexcept                                                                        \
{                                                                               \
    left.x compoundOp right;                                                    \
    left.y compoundOp right;                                                    \
    left.z compoundOp right;                                                    \
    left.w compoundOp right;                                                    \
    return left;                                                                \
}                                                                               \
                                                                                \
template<typename T, typename U>                                                \
VECTOR_DECL vec4<T>& operator compoundOp (vec4<T>& left, U right)               \
noexcept                                                                        \
{                                                                               \
    left.x compoundOp static_cast<T>(right);                                    \
    left.y compoundOp static_cast<T>(right);                                    \
    left.z compoundOp static_cast<T>(right);                                    \
    left.w compoundOp static_cast<T>(right);                                    \
    return left;                                                                \
}

VECTOR4_ARITHMETIC_DEF(+, +=)
VECTOR4_ARITHMETIC_DEF(-, -=)
VECTOR4_ARITHMETIC_DEF(*, *=)
VECTOR4_ARITHMETIC_DEF(/, /=)

template<typename T>
VECTOR_DECL vec4<T> operator-(const vec4<T> v)
{
    return vec3<T>(-v.x, -v.y, -v.z, -v.w);
}

//template <typename T>
//VECTOR_DECL vec4<T> operator*(T left, const vec4<T>& right)
//{
//    return vec3<T>(
//    right.x * left, right.y * left, right.z * left, right.w * left);
//}
//
//template<typename T, typename U>
//VECTOR_DECL vec4<T> operator*(U _left, const vec4<T>& right)
//{
//    const T left = static_cast<T>(_left);
//    return vec3<T>(
//    right.x * left, right.y * left, right.z * left, right.w * left);
//}

template <typename T>
VECTOR_DECL bool operator==(const vec4<T>& left, const vec4<T>& right)
{
    return
    (left.x == right.x) && (left.y == right.y) && 
    (left.z == right.z) && (left.w == right.w);
}

template <typename T>
VECTOR_DECL bool operator!=(const vec4<T>& left, const vec4<T>& right)
{
    return 
    (left.x != right.x) || (left.y != right.y) || 
    (left.z != right.z) || (left.w != right.w);
}

template <typename T, typename U>
bool operator!=(const vec4<T>& left, const vec4<U>& right)
{
    #if __cplusplus >= 201700L
    if constexpr (sizeof(T) >= sizeof(U))
    #else
    if (sizeof(T) >= sizeof(U))
    #endif
    {
        return
        (left.x != static_cast<T>(right.x)) && (left.y != static_cast<T>(right.y)) &&
        (left.z != static_cast<T>(right.z)) && (left.w != static_cast<T>(right.w));
    }
    #if __cplusplus >= 201700L
    else if constexpr (sizeof(T) < sizeof(U))
    #else
    else if (sizeof(T) < sizeof(U))
    #endif
    {
        return
        (static_cast<U>(left.x) != right.x) && (static_cast<U>(left.y) != right.y) &&
        (static_cast<U>(left.z) != right.z) && (static_cast<U>(left.w) != right.w);
    }
}

template <typename T, typename U>
bool operator==(const vec4<T>& left, const vec4<U>& right)
{
    #if __cplusplus >= 201700L
    if constexpr (sizeof(T) >= sizeof(U))
    #else
    if (sizeof(T) >= sizeof(U))
    #endif
    {
        return
        (left.x == static_cast<T>(right.x)) && (left.y == static_cast<T>(right.y)) &&
        (left.z == static_cast<T>(right.z)) && (left.w == static_cast<T>(right.w));
    }
    #if __cplusplus >= 201700L
    else if constexpr (sizeof(T) < sizeof(U))
    #else
    else if (sizeof(T) < sizeof(U))
    #endif
    {
        return
        (static_cast<U>(left.x) == right.x) && (static_cast<U>(left.y) == right.y) &&
        (static_cast<U>(left.z) == right.z) && (static_cast<U>(left.w) == right.w);
    }
}
}

using vec4b = core::vec4<unsigned char>;
using vec4c = core::vec4<char>;
using vec4u = core::vec4<unsigned int>;
using vec4i = core::vec4<int>;
using vec4f = core::vec4<float>;
using vec4d = core::vec4<double>;

#endif