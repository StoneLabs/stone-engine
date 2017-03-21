#if !defined(_SENG_NO_MATH_WARNING)
#pragma message ( "warning: Including single math classes is not supported. All math classes will be included. To suppress this warning import maths.h!" )
#endif

#include "maths.h"

#if !defined(_SENG_IS_DEFINED_VECTOR4F)
#define _SENG_IS_DEFINED_VECTOR4F
#include <iostream>

namespace seng
{
	namespace math
	{
		struct Vector4f
		{ 
			union
			{
				struct { float x, y, z, w; };
				float elements[4];
			};

			Vector4f() = default; //default default constructor
			Vector4f(const float &x, const float &y, const float &z, const float &w);

			Vector4f& add(const float &other);
			Vector4f& sub(const float &other);
			Vector4f& mul(const float &other);
			Vector4f& div(const float &other);
			Vector4f& add(const Vector4f &other);
			Vector4f& sub(const Vector4f &other);
			Vector4f& mul(const Vector4f &other);
			Vector4f& div(const Vector4f &other);


			Vector4f& operator+=(const float &right);
			Vector4f& operator-=(const float &right);
			Vector4f& operator*=(const float &right);
			Vector4f& operator/=(const float &right);
			Vector4f& operator+=(const Vector4f &right);
			Vector4f& operator-=(const Vector4f &right);
			Vector4f& operator*=(const Vector4f &right);
			Vector4f& operator/=(const Vector4f &right);
			bool	  operator==(const Vector4f &right) const;
			bool	  operator!=(const Vector4f &right) const;
			float&	  operator[](const int element);

			friend Vector4f operator+(Vector4f left, const float &right);
			friend Vector4f operator-(Vector4f left, const float &right);
			friend Vector4f operator*(Vector4f left, const float &right);
			friend Vector4f operator/(Vector4f left, const float &right);
			friend Vector4f operator+(Vector4f left, const Vector4f &right);
			friend Vector4f operator-(Vector4f left, const Vector4f &right);
			friend Vector4f operator*(Vector4f left, const Vector4f &right);
			friend Vector4f operator/(Vector4f left, const Vector4f &right);

			friend std::ostream& operator<<(std::ostream& stream, const Vector4f& vector);
		};
	}
}

#endif