#pragma once
#include <cmath>

namespace OT
{
    
    
    namespace Math
    {
        inline float sqrt(const float& x) {return ::sqrtf(x);}
        inline float cos(const float _rad) {return ::cosf(_rad);}
        inline float sin(const float _rad) {return ::sinf(_rad);}
        inline float tan(const float _rad) {return ::tanf(_rad);}
    }

    namespace MathExt
    {
        template <typename T> inline constexpr T kPi = static_cast<T>(3.14159265358979323846264338327950288L);
        template <typename T> constexpr T degToRad(const T deg ) {return (deg * ((kPi<T>)  / (T)180.0));};
    }

}
