#ifndef _VECTOR3_H_
#define _VECTOR3_H_


template<typename T>
class Vector3
{
public:
    T x, y, z;

    Vector3(): x(0), y(0),z(0){}

    Vector3(const Vector3<T>& v): 
        x(v.x), y(v.y), z(v.z){}

    template<typename U>
    explicit Vector3(const Vector3<U>& v):
        x(static_cast<T>(v.x)),
        y(static_cast<T>(v.y)),
        z(static_cast<T>(v.z)){}  

    Vector3(T x, T y, T z): 
        x(x), y(y), z(z){}

    bool isWithinRange(T _min, T _max)
    {
        return 
        x > _min && x < _max &&
        y > _min && y < _max &&
        z > _min && z < _max;
    }
};

#ifdef VECTOR_INLINE
#define VECTOR_DECL inline
#else
#define VECTOR_DECL
#endif

template<typename T>
VECTOR_DECL Vector3<T> operator-(const Vector3<T> v)
{
    return Vector3<T>(-v.x, -v.y, -v.z);
}

template <typename T>
VECTOR_DECL Vector3<T>& operator+=(
    Vector3<T>& left, const Vector3<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;
    return left;
}

template <typename T, typename U>
VECTOR_DECL Vector3<T>& operator+=(
    Vector3<T>& left, const Vector3<U>& right)
{
    left.x += static_cast<T>(right.x);
    left.y += static_cast<T>(right.y);
    left.z += static_cast<T>(right.z);
    return left;
}

template <typename T>
VECTOR_DECL Vector3<T>& operator-=(
    Vector3<T>& left, const Vector3<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;
    return left;
}

template <typename T, typename U>
VECTOR_DECL Vector3<T>& operator-=(
    Vector3<T>& left, const Vector3<U>& right)
{
    left.x -= static_cast<T>(right.x);
    left.y -= static_cast<T>(right.y);
    left.z -= static_cast<T>(right.z);
    return left;
}

template <typename T>
VECTOR_DECL Vector3<T> operator+(
    const Vector3<T>& left, const Vector3<T>& right)
{
    return Vector3<T>(
    left.x + right.x, 
    left.y + right.y, 
    left.z + right.z);
}

template <typename T, typename U>
VECTOR_DECL Vector3<T> operator+(
    const Vector3<T>& left, const Vector3<U>& right)
{
    return Vector3<T>(
    left.x + static_cast<T>(right.x),
    left.y + static_cast<T>(right.y),
    left.z + static_cast<T>(right.z));
}

template <typename T>
VECTOR_DECL Vector3<T> operator-(
    const Vector3<T>& left, const Vector3<T>& right)
{
    return Vector3<T>(
    left.x - right.x, 
    left.y - right.y, 
    left.z - right.z);
}

template <typename T, typename U>
VECTOR_DECL Vector3<T> operator-(
    const Vector3<T>& left, const Vector3<U>& right)
{
    return Vector3<T>(
    left.x - static_cast<T>(right.x),
    left.y - static_cast<T>(right.y),
    left.z - static_cast<T>(right.z));
}

template <typename T>
VECTOR_DECL Vector3<T> operator*(
    const Vector3<T>& left, T right)
{
    return Vector3<T>(
    left.x * right, 
    left.y * right, 
    left.z * right);
}

template <typename T, typename U>
VECTOR_DECL Vector3<T> operator*(
    const Vector3<T>& left, U _right)
{
    const T right = static_cast<T>(_right);
    return Vector3<T>(
    left.x * right, 
    left.y * right, 
    left.z * right);
}

template <typename T>
VECTOR_DECL Vector3<T> operator*(
    T left, const Vector3<T>& right)
{
    return Vector3<T>(
    right.x * left, 
    right.y * left, 
    right.z * left);
}

template<typename T, typename U>
VECTOR_DECL Vector3<T> operator*(
    U _left, const Vector3<T>& right)
{
    const T left = static_cast<T>(_left);
    return Vector3<T>(
    right.x * left, 
    right.y * left, 
    right.z * left);
}

template <typename T>
VECTOR_DECL Vector3<T>& operator*=(
    Vector3<T>& left, T right)
{
    left.x *= right;
    left.y *= right;
    left.z *= right;
    return left;
}

template <typename T, typename U>
VECTOR_DECL Vector3<T>& operator*=(
    Vector3<T>& left, U _right)
{
    const T right = static_cast<T>(_right);
    left.x *= right;
    left.y *= right;
    left.z *= right;
    return left;
}

template <typename T>
VECTOR_DECL Vector3<T> operator/(
    const Vector3<T>& left, T right)
{
    return Vector3<T>(
    left.x / right, 
    left.y / right, 
    left.z / right);
}

template <typename T, typename U>
VECTOR_DECL Vector3<T> operator/(
    const Vector3<T>& left, T _right)
{
    const T right = static_cast<T>(_right);
    return Vector3<T>(
    left.x / right, 
    left.y / right, 
    left.z / right);    
}

template <typename T>
VECTOR_DECL Vector3<T>& operator/=(
    Vector3<T>& left, T right)
{
    left.x /= right;
    left.y /= right;
    left.z /= right;
    return left;
}

template <typename T, typename U>
VECTOR_DECL Vector3<T>& operator/=(
    Vector3<T>& left, U _right)
{
    const T right = static_cast<T>(_right);
    left.x /= right;
    left.y /= right;
    left.z /= right;
    return left;   
}

template <typename T>
VECTOR_DECL bool operator==(
    const Vector3<T>& left, const Vector3<T>& right)
{
    return
    (left.x == right.x) && 
    (left.y == right.y) && 
    (left.z == right.z);
}

template <typename T>
VECTOR_DECL bool operator!=(
    const Vector3<T>& left, const Vector3<T>& right)
{
    return 
    (left.x != right.x) || 
    (left.y != right.y) || 
    (left.z != right.z);
}

template <typename T, typename U>
bool operator!=(
    const Vector3<T>& left, const Vector3<U>& right)
{
    //If one vector's value types have a larger size in bytes,
    //cast the other vector's types to those in order to prevent overflow.
    //If C++ 17 is enabled, use compile-time evaluation.

    #if __cplusplus >= 201700L
    if constexpr (sizeof(T) > sizeof(U))
    {
        return
        (left.x != static_cast<T>(right.x)) &&
        (left.y != static_cast<T>(right.y)) &&
        (left.z != static_cast<T>(right.z));
    }
    else if constexpr (sizeof(T) < sizeof(U))
    {
        return
        (static_cast<U>(left.x) != right.x) &&
        (static_cast<U>(left.y) != right.y) &&
        (static_cast<U>(left.z) != right.z);
    }
    else
    {
        return
        (left.x != static_cast<T>(right.x)) &&
        (left.y != static_cast<T>(right.y)) &&
        (left.z != static_cast<T>(right.z));
    }
    #else
    if (sizeof(T) > sizeof(U))
    {
        return
        (left.x != static_cast<T>(right.x)) &&
        (left.y != static_cast<T>(right.y)) &&
        (left.z != static_cast<T>(right.z));
    }
    else if (sizeof(T) < sizeof(U))
    {
        return
        (static_cast<U>(left.x) != right.x) &&
        (static_cast<U>(left.y) != right.y) &&
        (static_cast<U>(left.z) != right.z);
    }
    else
    {
        return
        (left.x != static_cast<T>(right.x)) &&
        (left.y != static_cast<T>(right.y)) &&
        (left.z != static_cast<T>(right.z));
    }
    #endif
}

template <typename T, typename U>
bool operator==(
    const Vector3<T>& left, const Vector3<U>& right)
{
    #if __cplusplus >= 201700L
    if constexpr (sizeof(T) > sizeof(U))
    {
        return
        (left.x == static_cast<T>(right.x)) &&
        (left.y == static_cast<T>(right.y)) &&
        (left.z == static_cast<T>(right.z));
    }
    else if constexpr (sizeof(T) < sizeof(U))
    {
        return
        (static_cast<U>(left.x) == right.x) &&
        (static_cast<U>(left.y) == right.y) &&
        (static_cast<U>(left.z) == right.z);
    }
    else
    {
        return
        (left.x == static_cast<T>(right.x)) &&
        (left.y == static_cast<T>(right.y)) &&
        (left.z == static_cast<T>(right.z));
    }
    #else
    if (sizeof(T) > sizeof(U))
    {
        return
        (left.x == static_cast<T>(right.x)) &&
        (left.y == static_cast<T>(right.y)) &&
        (left.z == static_cast<T>(right.z));
    }
    else if (sizeof(T) < sizeof(U))
    {
        return
        (static_cast<U>(left.x) == right.x) &&
        (static_cast<U>(left.y) == right.y) &&
        (static_cast<U>(left.z) == right.z);
    }
    else
    {
        return
        (left.x == static_cast<T>(right.x)) &&
        (left.y == static_cast<T>(right.y)) &&
        (left.z == static_cast<T>(right.z));
    }
    #endif
}
#endif