#if !defined(_SENG_NO_MATH_WARNING)
#pragma message ( "warning: Including single math classes is not supported. All math classes will be included. To suppress this warning import maths.h!" )
#endif

#include "maths.h"

#if !defined(_SENG_IS_DEFINED_VECTOR2F)
#define _SENG_IS_DEFINED_VECTOR2F
#include <iostream>

namespace seng
{
	namespace math
	{
		struct Vector2f
		{
			union
			{
				struct { float x, y; };
				float elements[2];
			};

			Vector2f() : Vector2f(0, 0) {}
			Vector2f(const float &x, const float &y);

			Vector2f& add(const float &other);
			Vector2f& sub(const float &other);
			Vector2f& mul(const float &other);
			Vector2f& div(const float &other);
			Vector2f& add(const Vector2f &other);
			Vector2f& sub(const Vector2f &other);
			Vector2f& mul(const Vector2f &other);
			Vector2f& div(const Vector2f &other);


			Vector2f& operator+=(const float &right);
			Vector2f& operator-=(const float &right);
			Vector2f& operator*=(const float &right);
			Vector2f& operator/=(const float &right);
			Vector2f& operator+=(const Vector2f &right);
			Vector2f& operator-=(const Vector2f &right);
			Vector2f& operator*=(const Vector2f &right);
			Vector2f& operator/=(const Vector2f &right);
			bool	  operator==(const Vector2f &right);
			bool	  operator!=(const Vector2f &right);
			float&	  operator[](const int element);

			friend Vector2f operator+(Vector2f left, const float &right);
			friend Vector2f operator-(Vector2f left, const float &right);
			friend Vector2f operator*(Vector2f left, const float &right);
			friend Vector2f operator/(Vector2f left, const float &right);
			friend Vector2f operator+(Vector2f left, const Vector2f &right);
			friend Vector2f operator-(Vector2f left, const Vector2f &right);
			friend Vector2f operator*(Vector2f left, const Vector2f &right);
			friend Vector2f operator/(Vector2f left, const Vector2f &right);

			friend std::ostream& operator<<(std::ostream& stream, const Vector2f& vector);
		};
	}
}

#endif