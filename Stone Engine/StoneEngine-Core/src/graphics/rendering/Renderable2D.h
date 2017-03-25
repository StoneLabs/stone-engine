#pragma once

#include "..\buffers\Buffer.h"
#include "..\buffers\IndexBuffer.h"
#include "..\buffers\VertexArray.h"
#include "..\Shader.h"
#include "..\..\math\maths.h"
#include "Renderer2D.h"

namespace seng
{
	namespace graphics
	{
		struct VertexData
		{
			math::Vector3f vertex;
			unsigned int color;
			math::Vector2f texCoord;
			//unsigned int texID;
		};

		class Renderable2D
		{
		protected:
			math::Vector3f m_position;
			math::Vector2f m_size;
			math::Vector4f m_color;
			std::vector<math::Vector2f> m_texCoord;

		protected:
			Renderable2D() { setTexCoordDefaults(); }
		public:
			Renderable2D(math::Vector3f position, math::Vector2f size, math::Vector4f color)
				: m_position(position), m_size(size), m_color(color) { setTexCoordDefaults(); }

			virtual ~Renderable2D() {}

			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			}

			inline const math::Vector3f& getPosition()	const { return m_position;	}
			inline const math::Vector2f& getSize()		const { return m_size;		}
			inline const math::Vector4f& getColor()		const { return m_color;		}
			inline const std::vector<seng::math::Vector2f> &getTexCoord() const { return m_texCoord; }
		private:
			void setTexCoordDefaults()
			{
				m_texCoord.push_back(math::Vector2f(0, 0));
				m_texCoord.push_back(math::Vector2f(0, 1));
				m_texCoord.push_back(math::Vector2f(1, 1));
				m_texCoord.push_back(math::Vector2f(1, 0));
			}
		};
	}
}