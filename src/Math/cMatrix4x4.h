#pragma once
#include "cVector3.h"
#include "cVector4.h"

namespace OT
{
    template<typename T>
    class cMatrix4x4
    {
    public:
        constexpr cMatrix4x4() = default;
        constexpr cMatrix4x4(const cVector3<T>& _x, const cVector3<T>& _y, const cVector3<T>& _z, const cVector3<T>& _w): x(_x, T(0)), y(_y, T(0)), z(_z, T(0)), w(_w, T(1)) {}
        constexpr cMatrix4x4(const cVector4<T>& _x, const cVector4<T>& _y, const cVector4<T>& _z, const cVector4<T>& _w): x(_x), y(_y), z(_z), w(_w) {}
        
        constexpr cMatrix4x4 operator+ (const cMatrix4x4& _m) const {return x + _m.x, y +_m.y, z+_m.z, w+_m.w;}

        cVector4<T> x = {T(1), T(0), T(0), T(0)};
        cVector4<T> y = {T(0), T(1), T(0), T(0)};
        cVector4<T> z = {T(0), T(0), T(1), T(0)};
        cVector4<T> w = {T(0), T(0), T(0), T(1)};

        cMatrix4x4<T> convertDXMatrix(DirectX::XMMATRIX& _m) const {return {_m.r[0], _m.r[1], _m.r[2], _m.r[3]};}
        inline cMatrix4x4& transpose();
        inline cMatrix4x4& lookAt(const cVector3<T>& _pos, const cVector3<T> _target, const cVector3<T> _up);
    
    };
    typedef cMatrix4x4<float> cMatrix4x4f;
    template <typename T>
    cMatrix4x4<T>& cMatrix4x4<T>::transpose()
    {
        *this = {
            {x.x,y.x,z.x,w.x},
            {x.y,y.y,z.y,w.y},
            {x.z,y.z,z.z,w.z},
            {x.w,y.w,z.w,w.w},
        };
        return *this;
    }
    template <typename T>
    cMatrix4x4<T>& cMatrix4x4<T>::lookAt(const cVector3<T>& _pos, const cVector3<T> _target, const cVector3<T> _up)
    {
        
    }


}


