/* Copyright (c) 2021 Anthony Constantinescu (Tonycons-dev)
 *
 * -Vector2.hpp-
 *      Two-dimensional vector with arithmetic functions
 *      (scalar and vector addition, subtraction, multiplication, division).
 */

#ifndef _CORE_VECTOR2_
#define _CORE_VECTOR2_

namespace core {

template<typename T>
struct vec2
{
public:
    T x, y;

    vec2() noexcept: x(0), y(0){}

    vec2(const vec2<T>& v) noexcept:
        x(v.x), y(v.y){}

    template<typename U>
    explicit vec2(const vec2<U>& v) :
        x(static_cast<T>(v.x)),
        y(static_cast<T>(v.y)){}  

    explicit vec2(T s) noexcept: x(s), y(s){}
    vec2(T x, T y) noexcept: x(x), y(y){}
};

#ifdef VECTOR_INLINE
#define VECTOR_DECL inline
#else
#define VECTOR_DECL
#endif

#define VECTOR2_ARITHMETIC_DEF(op, compoundOp)                                  \
                                                                                \
template<typename T>                                                            \
VECTOR_DECL vec2<T> operator op (const vec2<T>& left, const vec2<T>& right)     \
noexcept                                                                        \
{                                                                               \
    return vec2<T>(                                                             \
        left.x op right.x,                                                      \
        left.y op right.y);                                                     \
}                                                                               \
                                                                                \
template<typename T>                                                            \
VECTOR_DECL vec2<T> operator op (const vec2<T>& left, T right)                  \
noexcept                                                                        \
{                                                                               \
    return vec2<T>(                                                             \
        left.x op right,                                                        \
        left.y op right);                                                       \
}                                                                               \
                                                                                \
template<typename T, typename U>                                                \
VECTOR_DECL vec2<T> operator op (const vec2<T>& left, U right)                  \
noexcept                                                                        \
{                                                                               \
    return vec2<T>(                                                             \
        left.x op static_cast<T>(right),                                        \
        left.y op static_cast<T>(right));                                       \
}                                                                               \
                                                                                \
template<typename T, typename U>                                                \
VECTOR_DECL vec2<T> operator op (const vec2<T>& left, const vec2<U>& right)     \
noexcept                                                                        \
{                                                                               \
    return vec2<T>(                                                             \
        left.x op static_cast<T>(right.x),                                      \
        left.y op static_cast<T>(right.y));                                     \
}                                                                               \
                                                                                \
template<typename T>                                                            \
VECTOR_DECL vec2<T>& operator compoundOp (vec2<T>& left, const vec2<T>& right)  \
noexcept                                                                        \
{                                                                               \
    left.x compoundOp right.x;                                                  \
    left.y compoundOp right.y;                                                  \
    return left;                                                                \
}                                                                               \
                                                                                \
template<typename T, typename U>                                                \
VECTOR_DECL vec2<T>& operator compoundOp (vec2<T>& left, const vec2<U>& right)  \
noexcept                                                                        \
{                                                                               \
    left.x compoundOp static_cast<T>(right.x);                                  \
    left.y compoundOp static_cast<T>(right.y);                                  \
    return left;                                                                \
}                                                                               \
                                                                                \
template<typename T>                                                            \
VECTOR_DECL vec2<T>& operator compoundOp (vec2<T>& left, T right)               \
noexcept                                                                        \
{                                                                               \
    left.x compoundOp right;                                                    \
    left.y compoundOp right;                                                    \
    return left;                                                                \
}                                                                               \
                                                                                \
template<typename T, typename U>                                                \
VECTOR_DECL vec2<T>& operator compoundOp (vec2<T>& left, U right)               \
noexcept                                                                        \
{                                                                               \
    left.x compoundOp static_cast<T>(right);                                    \
    left.y compoundOp static_cast<T>(right);                                    \
    return left;                                                                \
}

VECTOR2_ARITHMETIC_DEF(+, +=)
VECTOR2_ARITHMETIC_DEF(-, -=)
VECTOR2_ARITHMETIC_DEF(*, *=)
VECTOR2_ARITHMETIC_DEF(/, /=)

template<typename T>
VECTOR_DECL vec2<T> operator-(const vec2<T> v)
noexcept
{
    return vec2<T>(-v.x, -v.y);
}

//template <typename T>
//VECTOR_DECL vec2<T> operator*(T left, const vec2<T>& right) noexcept
//{
//    return vec2<T>(right.x * left, right.y * left);
//}
//
//template<typename T, typename U>
//VECTOR_DECL vec2<T> operator*(U _left, const vec2<T>& right)
//{
//    const T left = static_cast<T>(_left);
//    return vec2<T>(right.x * left, right.y * left);
//}

template <typename T>
VECTOR_DECL bool operator==(const vec2<T>& left, const vec2<T>& right)
noexcept
{
    return(left.x == right.x) && (left.y == right.y);
}

template <typename T>
VECTOR_DECL bool operator!=(const vec2<T>& left, const vec2<T>& right)
noexcept
{
    return(left.x != right.x) || (left.y != right.y);
}

template <typename T, typename U>
bool operator!=(const vec2<T>& left, const vec2<U>& right) noexcept
{
    #if __cplusplus >= 201700L
    if constexpr (sizeof(T) >= sizeof(U))
    #else
    if (sizeof(T) >= sizeof(U))
    #endif
    {
        return
        (left.x != static_cast<T>(right.x)) && (left.y != static_cast<T>(right.y));
    }
    #if __cplusplus >= 201700L
    else if constexpr (sizeof(T) < sizeof(U))
    #else
    else if (sizeof(T) < sizeof(U))
    #endif
    {
        return
        (static_cast<U>(left.x) != right.x) && (static_cast<U>(left.y) != right.y);
    }
}

template <typename T, typename U>
bool operator==(const vec2<T>& left, const vec2<U>& right) noexcept
{
    #if __cplusplus >= 201700L
    if constexpr (sizeof(T) >= sizeof(U))
    #else
    if (sizeof(T) >= sizeof(U))
    #endif
    {
        return
        (left.x == static_cast<T>(right.x)) && (left.y == static_cast<T>(right.y));
    }
    #if __cplusplus >= 201700L
    else if constexpr (sizeof(T) < sizeof(U))
    #else
    else if (sizeof(T) < sizeof(U))
    #endif
    {
        return
        (static_cast<U>(left.x) == right.x) && (static_cast<U>(left.y) == right.y);
    }
}
}

using vec2b = core::vec2<unsigned char>;  
using vec2c = core::vec2<signed char>;
using vec2u = core::vec2<unsigned int>;
using vec2i = core::vec2<signed int>;
using vec2f = core::vec2<float>;
using vec2d = core::vec2<double>;

#endif