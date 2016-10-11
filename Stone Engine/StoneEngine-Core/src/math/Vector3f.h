#if !defined(_SENG_NO_MATH_WARNING)
#pragma message ( "warning: Including single math classes is not supported. All math classes will be included. To suppress this warning import maths.h!" )
#endif

#include "maths.h"

#if !defined(_SENG_IS_DEFINED_VECTOR3F)
#define _SENG_IS_DEFINED_VECTOR3F
#include <iostream>



namespace seng
{
	namespace math
	{
		struct Vector3f
		{
			union
			{
				struct { float x, y, z; };
				float elements[3];
			};

			Vector3f() : Vector3f(0, 0, 0) {}
			Vector3f(const float &x, const float &y, const float &z);

			Vector3f& add(const float &other);
			Vector3f& sub(const float &other);
			Vector3f& mul(const float &other);
			Vector3f& div(const float &other);
			Vector3f& add(const Vector3f &other);
			Vector3f& sub(const Vector3f &other);
			Vector3f& mul(const Vector3f &other);
			Vector3f& div(const Vector3f &other);


			Vector3f& operator+=(const float &right);
			Vector3f& operator-=(const float &right);
			Vector3f& operator*=(const float &right);
			Vector3f& operator/=(const float &right);
			Vector3f& operator+=(const Vector3f &right);
			Vector3f& operator-=(const Vector3f &right);
			Vector3f& operator*=(const Vector3f &right);
			Vector3f& operator/=(const Vector3f &right);
			bool	  operator==(const Vector3f &right);
			bool	  operator!=(const Vector3f &right);
			float&	  operator[](const int element);

			friend Vector3f operator+(Vector3f left, const float &right);
			friend Vector3f operator-(Vector3f left, const float &right);
			friend Vector3f operator*(Vector3f left, const float &right);
			friend Vector3f operator/(Vector3f left, const float &right);
			friend Vector3f operator+(Vector3f left, const Vector3f &right);
			friend Vector3f operator-(Vector3f left, const Vector3f &right);
			friend Vector3f operator*(Vector3f left, const Vector3f &right);
			friend Vector3f operator/(Vector3f left, const Vector3f &right);

			friend std::ostream& operator<<(std::ostream& stream, const Vector3f& vector);
		};
	}
}

#endif