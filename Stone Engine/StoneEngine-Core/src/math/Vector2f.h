#pragma once
#include <iostream>

namespace seng
{
	namespace math
	{
		struct Vector2f
		{
			float x, y;

			Vector2f() : Vector2f(0, 0) {}
			Vector2f(const float &x, const float &y);

			Vector2f& add(const Vector2f &other);
			Vector2f& sub(const Vector2f &other);
			Vector2f& mul(const Vector2f &other);
			Vector2f& div(const Vector2f &other);


			Vector2f& operator+=(const Vector2f &right);
			Vector2f& operator-=(const Vector2f &right);
			Vector2f& operator*=(const Vector2f &right);
			Vector2f& operator/=(const Vector2f &right);
			bool	  operator==(const Vector2f &right);
			bool	  operator!=(const Vector2f &right);

			friend Vector2f& operator+(Vector2f left, const Vector2f &right);
			friend Vector2f& operator-(Vector2f left, const Vector2f &right);
			friend Vector2f& operator*(Vector2f left, const Vector2f &right);
			friend Vector2f& operator/(Vector2f left, const Vector2f &right);

			friend std::ostream& operator<<(std::ostream& stream, const Vector2f& vector);
		};
	}
}