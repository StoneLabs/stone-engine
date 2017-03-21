#if !defined(_SENG_NO_MATH_WARNING)
#pragma message ( "warning: Including single math classes is not supported. All math classes will be included. To suppress this warning import maths.h!" )
#endif

#include "maths.h"

#if !defined(_SENG_IS_DEFINED_MATRIX4f)
#define _SENG_IS_DEFINED_MATRIX4f

namespace seng
{
	namespace math
	{
		struct Matrix4f //Column major
		{
			const static int MATRIX_EDGE_LENGTH = 4;
			const static int MATRIX_LENGTH = MATRIX_EDGE_LENGTH * MATRIX_EDGE_LENGTH;

			union
			{
				float elements[MATRIX_LENGTH];
				Vector4f columns[4];
			};

			Matrix4f();
			Matrix4f(float diagonal);

			static Matrix4f identity();
			static Matrix4f orthographic(float left, float right, float bottom, float top, float near, float far);
			static Matrix4f perspective(float fov, float aspectRatio, float near, float far);

			static Matrix4f translation(const Vector3f &translation);
			static Matrix4f rotation(float angle, const Vector3f &axis);
			static Matrix4f scale(const Vector3f &scale);

			Matrix4f& multiply(const Matrix4f &other);
			Vector3f  multiply(const Vector3f &other) const;
			Vector4f  multiply(const Vector4f &other) const;

			Matrix4f& operator*=(const Matrix4f &right);
			Vector4f& operator[](const int column);
			friend Matrix4f operator*(Matrix4f left, const Matrix4f &right);
			friend Vector3f operator*(const Matrix4f &left, const Vector3f &right);
			friend Vector4f operator*(const Matrix4f &left, const Vector4f &right);
		};
	}
}

#endif