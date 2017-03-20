#include "maths.h"

namespace seng
{
	namespace math
	{
#pragma region constructors
		Matrix4f::Matrix4f()
		{
			for (int i = 0; i < MATRIX_LENGTH; i++)
				elements[i] = 0.0f;
		}
		Matrix4f::Matrix4f(float diagonal)
		{
			for (int i = 0; i < MATRIX_LENGTH; i++)
				elements[i] = i % (MATRIX_EDGE_LENGTH + 1) ? 0 : diagonal;
		}
#pragma endregion

#pragma region static matrix stuff
		Matrix4f Matrix4f::identity() { return Matrix4f(1.0f); }

		Matrix4f Matrix4f::orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			Matrix4f result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top   - bottom);
			result.elements[2 + 2 * 4] = 2.0f / (near  - far);

			result.elements[0 + 3 * 4] = (left   + right) / (left   - right);
			result.elements[1 + 3 * 4] = (bottom + top)   / (bottom - top);
			result.elements[2 + 3 * 4] = (far    + near)  / (far    - near);

			return result;
		}
		Matrix4f Matrix4f::perspective(float fov, float aspectRatio, float near, float far)
		{
			Matrix4f result(1.0f);

			float n = 1 / tan(toRadians(0.5f * fov));
			float m = n / aspectRatio;

			float b = (near + far) / (near - far);
			float c = (2 * near * far) / (near - far);

			result.elements[0 + 0 * 4] = n;
			result.elements[1 + 1 * 4] = m;
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[2 + 3 * 4] = c;

			return result;
		}

		Matrix4f Matrix4f::translation(const Vector3f &translation)
		{
			Matrix4f result(1.0f);

			result.elements[0 + 3 * 4] = translation.x;
			result.elements[1 + 3 * 4] = translation.y;
			result.elements[2 + 3 * 4] = translation.z;

			return result;
		}
		Matrix4f Matrix4f::rotation(float angle, const Vector3f &axis)
		{
			Matrix4f result(1.0f);

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * 4] = x * omc + c;
			result.elements[1 + 0 * 4] = y * x * omc + z * s;
			result.elements[2 + 0 * 4] = x * z * omc - y * s;

			result.elements[0 + 1 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * omc + c;
			result.elements[2 + 1 * 4] = y * z * omc + x * s;

			result.elements[0 + 2 * 4] = x * z * omc + y * s;
			result.elements[1 + 2 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = z * omc + c;

			return result;
		}
		Matrix4f Matrix4f::scale(const Vector3f &scale)
		{
			Matrix4f result(1.0f);

			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;

			return result;
		}
#pragma endregion

#pragma region operators
		Matrix4f& Matrix4f::multiply(const Matrix4f &other)
		{
			float data[16];

			for (int y = 0; y < MATRIX_EDGE_LENGTH; y++)
				for (int x = 0; x < MATRIX_EDGE_LENGTH; x++)
				{
					float sum = 0.0f;
					for (int e = 0; e < MATRIX_EDGE_LENGTH; e++)
						sum += elements[x + e * MATRIX_EDGE_LENGTH] * other.elements[e + y * MATRIX_EDGE_LENGTH];

					data[x + y * MATRIX_EDGE_LENGTH] = sum;
				}

			memcpy(elements, data, 16);
			return *this;
		}

		Vector4f& Matrix4f::operator[](const int column) { return columns[column]; }

		Matrix4f& Matrix4f::operator*=(const Matrix4f &right) { return multiply(right); }
		Matrix4f operator*(Matrix4f left, const Matrix4f &right) { return left.multiply(right); }
#pragma endregion
	}
}