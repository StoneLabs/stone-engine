#pragma once

#include "..\buffers\Buffer.h"
#include "..\buffers\IndexBuffer.h"
#include "..\buffers\VertexArray.h"
#include "..\Shader.h"
#include "..\..\math\maths.h"
#include "Renderable2D.h"

namespace seng
{
	namespace graphics
	{
		class Sprite : public Renderable2D
		{
		private:
			
		public:
			Sprite(float x, float y, float width, float height,	const math::Vector4f &color);
		};
	}
}