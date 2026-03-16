#pragma once
#include <vector>

#include "cVector3.h"
class cMatrix4x4;
namespace OT
{
    template <typename T>
    class cVector4
    {
    public:
        constexpr cVector4() = default;
        constexpr cVector4(const T _x, const T _y, const T _z, const T _w): x(_x), y(_y), z(_z), w(_w) {}

        constexpr explicit cVector4(const cVector3<T>& _v);
        constexpr explicit cVector4(const cVector3<T>& _v, const T _w);

        constexpr cVector4 operator+ (const cVector4 _v) const {return {x + _v.x, y + _v.y, z + _v.z, w + _v.w};}

        inline cVector4& tranformVec(const cMatrix4x4<T>& _matrix);

        T x = T(0);
        T y = T(0);
        T z = T(0);
        T w = T(0);

        constexpr std::vector<T> ToVector() const
        {
            return {x,y,z,w};
            
        }         
    };
    typedef cVector4<float> cVector4f;

    template <typename T>
    cVector4<T>& cVector4<T>::tranformVec(const cMatrix4x4<T>& _matrix)
    {
        *this = {
            (x * _matrix.x.x) + (y * _matrix.y.x) + (z * _matrix.z.x) + (w * _matrix.w.x),
           (x * _matrix.x.y) + (y * _matrix.y.y) + (z * _matrix.z.y) + (w * _matrix.w.y),
           (x * _matrix.x.z) + (y * _matrix.y.z) + (z * _matrix.z.z) + (w * _matrix.w.z),
           (x * _matrix.x.w) + (y * _matrix.y.w) + (z * _matrix.z.w) + (w * _matrix.w.w)
        };
        return *this;
    }

}

