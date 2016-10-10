#pragma once
#include <iostream>

namespace seng
{
	namespace math
	{
		struct Vector4f
		{
			float x, y, z, w;

			Vector4f() : Vector4f(0, 0, 0, 0) {}
			Vector4f(const float &x, const float &y, const float &z, const float &w);

			Vector4f& add(const Vector4f &other);
			Vector4f& sub(const Vector4f &other);
			Vector4f& mul(const Vector4f &other);
			Vector4f& div(const Vector4f &other);


			Vector4f& operator+=(const Vector4f &right);
			Vector4f& operator-=(const Vector4f &right);
			Vector4f& operator*=(const Vector4f &right);
			Vector4f& operator/=(const Vector4f &right);
			bool	  operator==(const Vector4f &right);
			bool	  operator!=(const Vector4f &right);

			friend Vector4f& operator+(Vector4f left, const Vector4f &right);
			friend Vector4f& operator-(Vector4f left, const Vector4f &right);
			friend Vector4f& operator*(Vector4f left, const Vector4f &right);
			friend Vector4f& operator/(Vector4f left, const Vector4f &right);

			friend std::ostream& operator<<(std::ostream& stream, const Vector4f& vector);
		};
	}
}