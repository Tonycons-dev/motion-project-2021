#ifndef _VECTOR_2_H_
#define _VECTOR_2_H_

/* -Anthony Constantinescu-
* 
* Generic 2D vector for all integral types.
* Define VECTOR_INLINE to inline the operator functions.
*/
template<typename T>
class Vector2
{
public:
    T x, y;

    Vector2(): x(0), y(0){}

    Vector2(const Vector2<T>& v): 
        x(v.x), y(v.y){}

    template<typename U>
    explicit Vector2(const Vector2<U>& v):
        x(static_cast<T>(v.x)),
        y(static_cast<T>(v.y)){}  

    Vector2(T x, T y): x(x), y(y){}
};

#ifdef VECTOR_INLINE
#define VECTOR_DECL inline
#else
#define VECTOR_DECL
#endif

template<typename T>
VECTOR_DECL Vector2<T> operator-(const Vector2<T> v)
{
    return Vector2<T>(-v.x, -v.y);
}

template <typename T>
VECTOR_DECL Vector2<T>& operator+=(
    Vector2<T>& left, const Vector2<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    return left;
}

template <typename T, typename U>
VECTOR_DECL Vector2<T>& operator+=(
    Vector2<T>& left, const Vector2<U>& right)
{
    left.x += static_cast<T>(right.x);
    left.y += static_cast<T>(right.y);
    return left;
}

template <typename T>
VECTOR_DECL Vector2<T>& operator-=(
    Vector2<T>& left, const Vector2<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    return left;
}

template <typename T, typename U>
VECTOR_DECL Vector2<T>& operator-=(
    Vector2<T>& left, const Vector2<U>& right)
{
    left.x -= static_cast<T>(right.x);
    left.y -= static_cast<T>(right.y);
    return left;
}

template <typename T>
VECTOR_DECL Vector2<T> operator+(
    const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(
    left.x + right.x, 
    left.y + right.y);
}

template <typename T, typename U>
VECTOR_DECL Vector2<T> operator+(
    const Vector2<T>& left, const Vector2<U>& right)
{
    return Vector2<T>(
    left.x + static_cast<T>(right.x),
    left.y + static_cast<T>(right.y));
}

template <typename T>
VECTOR_DECL Vector2<T> operator-(
    const Vector2<T>& left, const Vector2<T>& right)
{
    return Vector2<T>(
    left.x - right.x, 
    left.y - right.y);
}

template <typename T, typename U>
VECTOR_DECL Vector2<T> operator-(
    const Vector2<T>& left, const Vector2<U>& right)
{
    return Vector2<T>(
    left.x - static_cast<T>(right.x),
    left.y - static_cast<T>(right.y));
}

template <typename T>
VECTOR_DECL Vector2<T> operator*(
    const Vector2<T>& left, T right)
{
    return Vector2<T>(
    left.x * right, 
    left.y * right);
}

template <typename T, typename U>
VECTOR_DECL Vector2<T> operator*(
    const Vector2<T>& left, U _right)
{
    const T right = static_cast<T>(_right);
    return Vector2<T>(
    left.x * right, 
    left.y * right);
}

template <typename T>
VECTOR_DECL Vector2<T> operator*(
    T left, const Vector2<T>& right)
{
    return Vector2<T>(
    right.x * left, 
    right.y * left);
}

template<typename T, typename U>
VECTOR_DECL Vector2<T> operator*(
    U _left, const Vector2<T>& right)
{
    const T left = static_cast<T>(_left);
    return Vector2<T>(
    right.x * left, 
    right.y * left);
}

template <typename T>
VECTOR_DECL Vector2<T>& operator*=(
    Vector2<T>& left, T right)
{
    left.x *= right;
    left.y *= right;
    return left;
}

template <typename T, typename U>
VECTOR_DECL Vector2<T>& operator*=(
    Vector2<T>& left, U _right)
{
    const T right = static_cast<T>(_right);
    left.x *= right;
    left.y *= right;
    return left;
}

template <typename T>
VECTOR_DECL Vector2<T> operator/(
    const Vector2<T>& left, T right)
{
    return Vector2<T>(
    left.x / right, 
    left.y / right);
}

template <typename T, typename U>
VECTOR_DECL Vector2<T> operator/(
    const Vector2<T>& left, T _right)
{
    const T right = static_cast<T>(_right);
    return Vector2<T>(
    left.x / right, 
    left.y / right);    
}

template <typename T>
VECTOR_DECL Vector2<T>& operator/=(
    Vector2<T>& left, T right)
{
    left.x /= right;
    left.y /= right;
    return left;
}

template <typename T, typename U>
VECTOR_DECL Vector2<T>& operator/=(
    Vector2<T>& left, U _right)
{
    const T right = static_cast<T>(_right);
    left.x /= right;
    left.y /= right;
    return left;   
}

template <typename T>
VECTOR_DECL bool operator==(
    const Vector2<T>& left, const Vector2<T>& right)
{
    return
    (left.x == right.x) && 
    (left.y == right.y);
}

template <typename T>
VECTOR_DECL bool operator!=(
    const Vector2<T>& left, const Vector2<T>& right)
{
    return 
    (left.x != right.x) || 
    (left.y != right.y);
}

template <typename T, typename U>
bool operator!=(
    const Vector2<T>& left, const Vector2<U>& right)
{
    //If one vector's value types have a larger size in bytes,
    //cast the other vector's types to those in order to prevent overflow.
    //If C++ 17 is enabled, use compile-time evaluation.

    #if __cplusplus >= 201700L
    if constexpr (sizeof(T) > sizeof(U))
    {
        return
        (left.x != static_cast<T>(right.x)) &&
        (left.y != static_cast<T>(right.y));
    }
    else if constexpr (sizeof(T) < sizeof(U))
    {
        return
        (static_cast<U>(left.x) != right.x) &&
        (static_cast<U>(left.y) != right.y));
    }
    else
    {
        return
        (left.x != static_cast<T>(right.x)) &&
        (left.y != static_cast<T>(right.y));
    }
    #else
    if (sizeof(T) > sizeof(U))
    {
        return
        (left.x != static_cast<T>(right.x)) &&
        (left.y != static_cast<T>(right.y));
    }
    else if (sizeof(T) < sizeof(U))
    {
        return
        (static_cast<U>(left.x) != right.x) &&
        (static_cast<U>(left.y) != right.y);
    }
    else
    {
        return
        (left.x != static_cast<T>(right.x)) &&
        (left.y != static_cast<T>(right.y));
    }
    #endif
}

template <typename T, typename U>
bool operator==(
    const Vector2<T>& left, const Vector2<U>& right)
{
    #if __cplusplus >= 201700L
    if constexpr (sizeof(T) > sizeof(U))
    {
        return
        (left.x == static_cast<T>(right.x)) &&
        (left.y == static_cast<T>(right.y));
    }
    else if constexpr (sizeof(T) < sizeof(U))
    {
        return
        (static_cast<U>(left.x) == right.x) &&
        (static_cast<U>(left.y) == right.y));
    }
    else
    {
        return
        (left.x == static_cast<T>(right.x)) &&
        (left.y == static_cast<T>(right.y));
    }
    #else
    if (sizeof(T) > sizeof(U))
    {
        return
        (left.x == static_cast<T>(right.x)) &&
        (left.y == static_cast<T>(right.y));
    }
    else if (sizeof(T) < sizeof(U))
    {
        return
        (static_cast<U>(left.x) == right.x) &&
        (static_cast<U>(left.y) == right.y);
    }
    else
    {
        return
        (left.x == static_cast<T>(right.x)) &&
        (left.y == static_cast<T>(right.y));
    }
    #endif
}

#endif