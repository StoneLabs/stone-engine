#include "Sprite.h"
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
		Sprite::Sprite(float x, float y, float width, float height, const math::Vector4f &color)
			: Renderable2D(math::Vector3f(x, y, 0), math::Vector2f(width, height), color) { }

		Sprite::Sprite(float x, float y, float width, float height, Texture *texture)
			: Renderable2D(math::Vector3f(x, y, 0), math::Vector2f(width, height), math::Vector4f(1, 0, 1, 1))
		{
			m_texture = texture;
		}

	}
}