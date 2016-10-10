#include "Vector2f.h"

namespace seng
{
	namespace math
	{
		Vector2f::Vector2f(const float &x, const float &y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2f& Vector2f::add(const Vector2f &other)
		{
			this->x += other.x;
			this->y += other.y;

			return *this;
		}

		Vector2f& Vector2f::sub(const Vector2f &other)
		{
			this->x -= other.x;
			this->y -= other.y;

			return *this;
		}

		Vector2f& Vector2f::mul(const Vector2f &other)
		{
			this->x *= other.x;
			this->y *= other.y;

			return *this;
		}

		Vector2f& Vector2f::div(const Vector2f &other)
		{
			this->x /= other.x;
			this->y /= other.y;

			return *this;
		}

		Vector2f& operator+(Vector2f left, const Vector2f &right) { return left.add(right); } 
		Vector2f& operator-(Vector2f left, const Vector2f &right) { return left.sub(right); }
		Vector2f& operator*(Vector2f left, const Vector2f &right) { return left.mul(right); }
		Vector2f& operator/(Vector2f left, const Vector2f &right) { return left.div(right); }

		Vector2f& Vector2f::operator+=(const Vector2f &right) { return add(right); }
		Vector2f& Vector2f::operator-=(const Vector2f &right) { return sub(right); }
		Vector2f& Vector2f::operator*=(const Vector2f &right) { return mul(right); }
		Vector2f& Vector2f::operator/=(const Vector2f &right) { return div(right); }
		bool	  Vector2f::operator==(const Vector2f &right) { return this->x == right.x && this->y == right.y; }
		bool	  Vector2f::operator!=(const Vector2f &right) { return this->x != right.x || this->y != right.y; }

		std::ostream& operator<<(std::ostream& stream, const Vector2f& vector)
		{
			stream << "(" << vector.x << " | " << vector.y << ")";
			return stream;
		}
	}
}