template <typename T>
Vector3<T>::Vector3() :
    x(0),
    y(0),
    z(0)
{
}

template <typename T>
Vector3<T>::Vector3(T const& x, T const& y, T const& z) :
    x(x),
    y(y),
    z(z)
{
}

template <typename T>
template <typename U>
Vector3<T>::Vector3(Vector3<U> const& vector) :
    x(static_cast<T>(vector.x)),
    y(static_cast<T>(vector.y)),
    z(static_cast<T>(vector.z))
{
}

template <typename T>
Vector3<T> operator -(Vector3<T> const& left)
{
    return Vector3<T>(-left.x, -left.y, -left.z);
}

template <typename T>
Vector3<T> operator +(Vector3<T> const& left, Vector3<T> const& right)
{
    return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

template <typename T>
Vector3<T>& operator +=(Vector3<T>& left, const Vector3<T>& right)
{
    left.x += right.x;
    left.y += right.y;
    left.z += right.z;

    return left;
}

template <typename T>
Vector3<T> operator -(Vector3<T> const& left, Vector3<T> const& right)
{
    return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

template <typename T>
Vector3<T>& operator -=(Vector3<T>& left, const Vector3<T>& right)
{
    left.x -= right.x;
    left.y -= right.y;
    left.z -= right.z;

    return left;
}

template <typename T>
Vector3<T> operator *(Vector3<T> const& left, T right)
{
    return Vector3<T>(left.x * right, left.y * right, left.z * right);
}

template <typename T>
Vector3<T> operator *(T left, Vector3<T> const& right)
{
    return Vector3<T>(left * right.x, left * right.y, left * right.z);
}

template <typename T>
Vector3<T>& operator *=(Vector3<T>& left, T right)
{
    left.x *= right;
    left.y *= right;
    left.z *= right;

    return left;
}

template <typename T>
Vector3<T> operator /(Vector3<T> const& left, T right)
{
    return Vector3<T>(left.x / right, left.y / right, left.z / right);
}

template <typename T>
Vector3<T>& operator /=(Vector3<T>& left, T right)
{
    left.x /= right;
    left.y /= right;
    left.z /= right;

    return left;
}

template <typename T>
bool operator ==(Vector3<T> const& left, Vector3<T> const& right)
{
    return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}

template <typename T>
bool operator !=(Vector3<T> const& left, Vector3<T> const& right)
{
    return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
}
