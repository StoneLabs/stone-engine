#include "maths.h"

namespace seng
{
	namespace math
	{
		Vector3f::Vector3f(const float &x, const float &y, const float &z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3f& Vector3f::add(const float &other)
		{
			this->x += other;
			this->y += other;
			this->z += other;

			return *this;
		}

		Vector3f& Vector3f::sub(const float &other)
		{
			this->x -= other;
			this->y -= other;
			this->z -= other;

			return *this;
		}

		Vector3f& Vector3f::mul(const float &other)
		{
			this->x *= other;
			this->y *= other;
			this->z *= other;

			return *this;
		}

		Vector3f& Vector3f::div(const float &other)
		{
			this->x /= other;
			this->y /= other;
			this->z /= other;

			return *this;
		}

		Vector3f& Vector3f::add(const Vector3f &other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;

			return *this;
		}

		Vector3f& Vector3f::sub(const Vector3f &other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;

			return *this;
		}

		Vector3f& Vector3f::mul(const Vector3f &other)
		{
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;

			return *this;
		}

		Vector3f& Vector3f::div(const Vector3f &other)
		{
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;

			return *this;
		}

		Vector3f operator+(Vector3f left, const float &right) { return left.add(right); }
		Vector3f operator-(Vector3f left, const float &right) { return left.sub(right); }
		Vector3f operator*(Vector3f left, const float &right) { return left.mul(right); }
		Vector3f operator/(Vector3f left, const float &right) { return left.div(right); }
		Vector3f operator+(Vector3f left, const Vector3f &right) { return left.add(right); } 
		Vector3f operator-(Vector3f left, const Vector3f &right) { return left.sub(right); }
		Vector3f operator*(Vector3f left, const Vector3f &right) { return left.mul(right); }
		Vector3f operator/(Vector3f left, const Vector3f &right) { return left.div(right); }

		Vector3f& Vector3f::operator+=(const float &right) { return add(right); }
		Vector3f& Vector3f::operator-=(const float &right) { return sub(right); }
		Vector3f& Vector3f::operator*=(const float &right) { return mul(right); }
		Vector3f& Vector3f::operator/=(const float &right) { return div(right); }
		Vector3f& Vector3f::operator+=(const Vector3f &right) { return add(right); }
		Vector3f& Vector3f::operator-=(const Vector3f &right) { return sub(right); }
		Vector3f& Vector3f::operator*=(const Vector3f &right) { return mul(right); }
		Vector3f& Vector3f::operator/=(const Vector3f &right) { return div(right); }
		bool	  Vector3f::operator==(const Vector3f &right) { return this->x == right.x && this->y == right.y && this->z == right.z; }
		bool	  Vector3f::operator!=(const Vector3f &right) { return this->x != right.x || this->y != right.y || this->z != right.z; }
		float&	  Vector3f::operator[](const int element) { return elements[element]; }

		std::ostream& operator<<(std::ostream& stream, const Vector3f& vector)
		{
			stream << "(" << vector.x << " | " << vector.y << " | " << vector.z << ")";
			return stream;
		}
	}
}