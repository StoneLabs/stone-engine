#include "maths.h"

namespace seng
{
	namespace math
	{
		Vector4f::Vector4f(const float &x, const float &y, const float &z, const float &w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector4f& Vector4f::add(const float &other)
		{
			this->x += other;
			this->y += other;
			this->z += other;
			this->w += other;

			return *this;
		}

		Vector4f& Vector4f::sub(const float &other)
		{
			this->x -= other;
			this->y -= other;
			this->z -= other;
			this->w -= other;

			return *this;
		}

		Vector4f& Vector4f::mul(const float &other)
		{
			this->x *= other;
			this->y *= other;
			this->z *= other;
			this->w *= other;

			return *this;
		}

		Vector4f& Vector4f::div(const float &other)
		{
			this->x /= other;
			this->y /= other;
			this->z /= other;
			this->w /= other;

			return *this;
		}

		Vector4f& Vector4f::add(const Vector4f &other)
		{
			this->x += other.x;
			this->y += other.y;
			this->z += other.z;
			this->w += other.w;

			return *this;
		}

		Vector4f& Vector4f::sub(const Vector4f &other)
		{
			this->x -= other.x;
			this->y -= other.y;
			this->z -= other.z;
			this->w -= other.w;

			return *this;
		}

		Vector4f& Vector4f::mul(const Vector4f &other)
		{
			this->x *= other.x;
			this->y *= other.y;
			this->z *= other.z;
			this->w *= other.w;

			return *this;
		}

		Vector4f& Vector4f::div(const Vector4f &other)
		{
			this->x /= other.x;
			this->y /= other.y;
			this->z /= other.z;
			this->w /= other.w;

			return *this;
		}

		Vector4f operator+(Vector4f left, const float &right) { return left.add(right); }
		Vector4f operator-(Vector4f left, const float &right) { return left.sub(right); }
		Vector4f operator*(Vector4f left, const float &right) { return left.mul(right); }
		Vector4f operator/(Vector4f left, const float &right) { return left.div(right); }
		Vector4f operator+(Vector4f left, const Vector4f &right) { return left.add(right); } 
		Vector4f operator-(Vector4f left, const Vector4f &right) { return left.sub(right); }
		Vector4f operator*(Vector4f left, const Vector4f &right) { return left.mul(right); }
		Vector4f operator/(Vector4f left, const Vector4f &right) { return left.div(right); }

		Vector4f& Vector4f::operator+=(const float &right) { return add(right); }
		Vector4f& Vector4f::operator-=(const float &right) { return sub(right); }
		Vector4f& Vector4f::operator*=(const float &right) { return mul(right); }
		Vector4f& Vector4f::operator/=(const float &right) { return div(right); }
		Vector4f& Vector4f::operator+=(const Vector4f &right) { return add(right); }
		Vector4f& Vector4f::operator-=(const Vector4f &right) { return sub(right); }
		Vector4f& Vector4f::operator*=(const Vector4f &right) { return mul(right); }
		Vector4f& Vector4f::operator/=(const Vector4f &right) { return div(right); }
		bool	  Vector4f::operator==(const Vector4f &right) const { return this->x == right.x && this->y == right.y && this->z == right.z && this->w == right.w; }
		bool	  Vector4f::operator!=(const Vector4f &right) const { return this->x != right.x || this->y != right.y || this->z != right.z || this->w != right.w; }
		float&	  Vector4f::operator[](const int element) { return elements[element]; }

		std::ostream& operator<<(std::ostream& stream, const Vector4f& vector)
		{
			stream << "(" << vector.x << " | " << vector.y << " | " << vector.z << " | " << vector.w << ")";
			return stream;
		}
	}
}