#pragma once

#include "..\buffers\Buffer.h"
#include "..\buffers\IndexBuffer.h"
#include "..\buffers\VertexArray.h"
#include "..\Shader.h"
#include "..\..\math\maths.h"

namespace seng
{
	namespace graphics
	{
		struct VertexData
		{
			math::Vector3f vertex;
			unsigned int color;
		};

		class Renderable2D
		{
		protected:
			math::Vector3f m_position;
			math::Vector2f m_size;
			math::Vector4f m_color;

		public:
			Renderable2D(math::Vector3f position, math::Vector2f size, math::Vector4f color)
				: m_position(position), m_size(size), m_color(color) { }

			virtual ~Renderable2D() {}

			inline const math::Vector3f& getPosition()	const { return m_position;	}
			inline const math::Vector2f& getSize()		const { return m_size;		}
			inline const math::Vector4f& getColor()		const { return m_color;		}
		};
	}
}