#pragma once

#include <glew.h>
#include "..\..\math\maths.h"
#include "Renderable2D.h"

namespace seng
{
	namespace graphics
	{
		class Renderer2D
		{
		public:
			virtual void submit(const Renderable2D *renderable) = 0;
			virtual void flush() = 0;
			virtual void begin() {};
			virtual void end() {};
		};
	}
}