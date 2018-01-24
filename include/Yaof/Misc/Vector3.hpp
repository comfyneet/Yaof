#ifndef YAOF_MISC_VECTOR3_HPP
#define YAOF_MISC_VECTOR3_HPP

#include "Yaof/Misc/Macros.hpp"

namespace yf
{
    template <typename T>
    class YAOF_TEMPLATE_DLL Vector3
    {
    public:
        Vector3();

        Vector3(T const& x, T const& y, T const& z);

        template <typename U>
        explicit Vector3(Vector3<U> const& vector);

        T x;

        T y;

        T z;
    };

    template <typename T>
    Vector3<T> operator -(Vector3<T> const& left);

    template <typename T>
    Vector3<T> operator +(Vector3<T> const& left, Vector3<T> const& right);

    template <typename T>
    Vector3<T>& operator +=(Vector3<T>& left, const Vector3<T>& right);

    template <typename T>
    Vector3<T> operator -(const Vector3<T>& left, const Vector3<T>& right);

    template <typename T>
    Vector3<T>& operator -=(Vector3<T>& left, const Vector3<T>& right);

    template <typename T>
    Vector3<T> operator *(const Vector3<T>& left, T right);

    template <typename T>
    Vector3<T> operator *(T left, Vector3<T> const& right);

    template <typename T>
    Vector3<T>& operator *=(Vector3<T>& left, T right);

    template <typename T>
    Vector3<T> operator /(Vector3<T> const& left, T right);

    template <typename T>
    Vector3<T>& operator /=(Vector3<T>& left, T right);

    template <typename T>
    bool operator ==(const Vector3<T>& left, const Vector3<T>& right);

    template <typename T>
    bool operator !=(const Vector3<T>& left, const Vector3<T>& right);

#include "Yaof/Misc/Vector3.inl"
}

#endif
