#pragma once
#include "cMath.h"
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
        
        cVector3<T>& left(void) {return *reinterpret_cast<cVector3<T>*>(&x);}
        const cVector3<T>& left(void) const {return *reinterpret_cast<const cVector3<T>*>(&x);}
        cVector3<T>& up(void) {return *reinterpret_cast<cVector3<T>*>(&y);}
        const cVector3<T>& up(void) const {return *reinterpret_cast<const cVector3<T>*>(&y);}
        cVector3<T>& at(void) {return *reinterpret_cast<cVector3<T>*>(&z);}
        const cVector3<T>& at(void) const {return *reinterpret_cast<const cVector3<T>*>(&z);}
        cVector3<T>& pos(void) {return *reinterpret_cast<cVector3<T>*>(&w);}
        const cVector3<T>& pos(void) const {return *reinterpret_cast<const cVector3<T>*>(&w);}

        cVector4<T> x = {T(1), T(0), T(0), T(0)};
        cVector4<T> y = {T(0), T(1), T(0), T(0)};
        cVector4<T> z = {T(0), T(0), T(1), T(0)};
        cVector4<T> w = {T(0), T(0), T(0), T(1)};
        
        inline cMatrix4x4& transpose();
        inline cMatrix4x4& lookAt(const cVector3<T>& _pos, const cVector3<T> _target, const cVector3<T> _up);
        inline cMatrix4x4& rotate(const cVector3<T>& axis, const T angle);
        inline cMatrix4x4& perspective(const T _fov, const T _aspect, const T _near, const T _far);
    
    };

    typedef cMatrix4x4<float> cMatrix4x4f;
    namespace Matrix4x4
    {
        template <typename T> inline cMatrix4x4<T> rotate(const cVector3<T>& axis, const T angle) {return cMatrix4x4<T>().rotate(axis, angle);}       
        template <typename T> inline cMatrix4x4<T> perspective(const T _fov, const T _aspect, const T _near, const T _far) {return cMatrix4x4<T>().perspective(_fov, _aspect, _near, _far);}       
    }
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
        const cVector3<T> nz = Vector3::normalize(_target - _pos);
        const cVector3<T> nx = Vector3::normalize(Vector3::cross(_up, nz));
        
        *this = 
        {
            cVector4<T>{nx, T(0)},
            cVector4<T>{Vector3::cross(nz, nx), T(0)},
            cVector4<T>{nz, T(0)},
            cVector4<T>{_pos, T(0)},
        };
        
        return *this;
    }
    
    template <typename T>
    inline cMatrix4x4<T>& cMatrix4x4<T>::perspective(const T _fov, const T _aspect, const T _near, const T _far)
    {
        const T cotan = T(1) / Math::tan(MathExt::degToRad(_fov / T(2)));
        const T depth = _far - _near;
        const T xx = -cotan;
        const T yy = cotan * _aspect;
        
        *this = 
        {
            {xx, T(0), T(0), T(0)},
            {T(0), yy, T(0), T(0)},
            {T(0), T(0), _far / depth, T(1) },
            {T(0),T(0), -(_far * _near) / depth, T(0)}
        };
        return *this;
    }
    
    template <typename T>
    inline cMatrix4x4<T>& cMatrix4x4<T>::rotate(const cVector3<T>& axis, const T angle)
    {
        const T rad = MathExt::degToRad(angle);
        const T s = Math::sin(rad);
        const T c = Math::cos(rad);
        const T t = T(1) - c;
        const T tx = t * axis.x;
        const T ty = t * axis.y;
        const T tz = t * axis.z;
        const T sx = s * axis.x;
        const T sy = s * axis.y;
        const T sz = s * axis.z;
        
        *this = 
        {
            {tx * axis.x + c, tx * axis.y - sz, tx * axis.z + sy, T(0)},
            {ty * axis.x + sz, ty * axis.y + c, ty * axis.z - sx, T(0)},
            {tz * axis.x - sy, tz * axis.y + sx, tz * axis.z + c, T(0)},
            {T(0),T(0),T(0),T(1)}
        };
        return *this;
    }


}


