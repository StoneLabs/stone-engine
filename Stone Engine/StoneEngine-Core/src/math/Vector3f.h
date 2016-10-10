#pragma once
#include <iostream>

namespace seng
{
	namespace math
	{
		struct Vector3f
		{
			float x, y, z;

			Vector3f() : Vector3f(0, 0, 0) {}
			Vector3f(const float &x, const float &y, const float &z);

			Vector3f& add(const Vector3f &other);
			Vector3f& sub(const Vector3f &other);
			Vector3f& mul(const Vector3f &other);
			Vector3f& div(const Vector3f &other);


			Vector3f& operator+=(const Vector3f &right);
			Vector3f& operator-=(const Vector3f &right);
			Vector3f& operator*=(const Vector3f &right);
			Vector3f& operator/=(const Vector3f &right);
			bool	  operator==(const Vector3f &right);
			bool	  operator!=(const Vector3f &right);

			friend Vector3f& operator+(Vector3f left, const Vector3f &right);
			friend Vector3f& operator-(Vector3f left, const Vector3f &right);
			friend Vector3f& operator*(Vector3f left, const Vector3f &right);
			friend Vector3f& operator/(Vector3f left, const Vector3f &right);

			friend std::ostream& operator<<(std::ostream& stream, const Vector3f& vector);
		};
	}
}