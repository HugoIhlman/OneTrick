#pragma once
class cMatrix4x4;
namespace OT
{
    template <typename T>
    class cVector3
    {
    public:
        constexpr cVector3() = default;
        constexpr cVector3(const T _x, const T _y, const T _z) : x(_x), y(_y), z(_z) {}
        constexpr explicit cVector3( const T _t) : x(_t), y(_t), z(_t) {}

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


        T x = T(0);
        T y = T(0);
        T z = T(0);

        

        
    };
        typedef cVector3<float> cVector3f;
    template<typename T>
    cVector3<T>& cVector3<T>::tranformVec(const cMatrix4x4<T>& _matrix)
    {
        *this = {
            (x * _matrix.x.x) + (y * _matrix.y.x) + (z * _matrix.z.x),
           (x * _matrix.x.y) + (y * _matrix.y.y) + (z * _matrix.z.y),
           (x * _matrix.x.z) + (y * _matrix.y.z) + (z * _matrix.z.z),
           (x * _matrix.x.w) + (y * _matrix.y.w) + (z * _matrix.z.w)
        };
        return *this;
    }
    
}

