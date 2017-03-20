#pragma once

#define _SENG_NO_MATH_WARNING
#define _USE_MATH_DEFINES
#include <math.h>

namespace seng
{
	namespace math
	{
		inline float toRadians(float degrees)
		{
			return (float)(degrees * (M_PI / 180.0f));
		}
		inline float toDegrees(float radians)
		{
			return (float)(radians / M_PI * 180.0f);
		}
	}
}

#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"
#include "Matrix4f.h"