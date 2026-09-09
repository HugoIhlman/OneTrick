#pragma once
namespace OT
{
    template <typename T>class cMatrix4x4;

    template <typename T>
    class cVector3
    {
    public:
        constexpr cVector3() = default;
        constexpr cVector3(const T _x, const T _y, const T _z) : x(_x), y(_y), z(_z) {}
        constexpr explicit cVector3( const T _t) : x(_t), y(_t), z(_t) {}
        template <typename T2>
        constexpr explicit cVector3(const cVector3<T2>& _v);

        ////////////////////////////////// operators /////////////////////////////////////////////

        constexpr cVector3 operator- () const {return {-x,-y,-z};}
        
        constexpr cVector3 operator+ (const cVector3& _v) const {return {x + _v.x, y + _v.y, z + _v.z};}
        constexpr cVector3 operator- (const cVector3& _v) const {return {x - _v.x, y - _v.y, z - _v.z};}
        constexpr cVector3 operator* (const cVector3& _v) const {return {x * _v.x, y * _v.y, z * _v.z};}
        constexpr cVector3 operator/ (const cVector3& _v) const {return {x / _v.x, y / _v.y, z / _v.z};}

        template<typename T2>
        constexpr cVector3 operator* (const T2 _t) const {return {static_cast<T>(x * _t), static_cast<T>(y * _t), static_cast<T>(z * _t)};}
        template<typename T2>
        constexpr cVector3 operator/ (const T2 _t) const {return {static_cast<T>(x / _t), static_cast<T>(y / _t), static_cast<T>(z / _t)};}

        inline cVector3& tranformVec(const cMatrix4x4<T>& _matrix);
        inline T length(void) const {return Math::sqrt(dot());}
        constexpr T dot (void) const {return (x * x) + (y * y) + (z * z);}
        inline cVector3& normalize(const T _length) {*this *= (_length > T(0)  ) ? (T(1) / _length): T(0);}
        inline cVector3& normalize(void) {normalize(length()); return *this;}
        inline cVector3& cross(const cVector3<T>& _vector) {*this = {(y * _vector.z) - (z * _vector.y), (z * _vector.x) - (x * _vector.z), (x * _vector.y) - (y * _vector.x)}; return *this;}

        T x = T(0);
        T y = T(0);
        T z = T(0);

        

        
    };
        typedef cVector3<float> cVector3f;
    
    
    
    namespace Vector3
    {
        template <typename T> constexpr cVector3<T> cross(const cVector3<T>& _v1, const cVector3<T>& _v2) {return {(_v1.y * _v2.z) - (_v1.z * _v2.y), (_v1.z * _v2.x) - (_v1.x * _v2.z), (_v1.x * _v2.y) - (_v1.y * _v2.x)};}
        template <typename T> constexpr  cVector3<T> normalize(const cVector3<T>& _vector, const T _length) {return (_length > T(0)) ? (_vector / _length) : cVector3<T>(T(0));}
        template <typename T> inline cVector3<T> normalize(const cVector3<T>& _vector) {return normalize(_vector, _vector.length());}
        template <typename T> inline cVector3<T> tranformVec(const cVector3<T>& _vector, const cMatrix4x4<T>& _m) {return cVector3<T>(_vector).tranformVec(_m);}
        
    }
    
    
}

namespace OT
{
    template <typename T> template <typename T2>
    constexpr cVector3<T>::cVector3(const cVector3<T2>& _v): x(static_cast<T>(_v.x)), y(static_cast<T>(_v.y)),z(static_cast<T>(_v.z)){}

    
    template<typename T>
    inline cVector3<T>& cVector3<T>::tranformVec(const cMatrix4x4<T>& _matrix)
    {
        *this = {
            (x * _matrix.x.x) + (y * _matrix.y.x) + (z * _matrix.z.x),
           (x * _matrix.x.y) + (y * _matrix.y.y) + (z * _matrix.z.y),
           (x * _matrix.x.z) + (y * _matrix.y.z) + (z * _matrix.z.z)
        };
        return *this;
    }    
}

