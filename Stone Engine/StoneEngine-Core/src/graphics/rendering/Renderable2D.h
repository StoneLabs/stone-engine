#pragma once

#include "..\buffers\Buffer.h"
#include "..\buffers\IndexBuffer.h"
#include "..\buffers\VertexArray.h"
#include "..\Shader.h"
#include "..\..\math\maths.h"
#include "Texture.h"
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
			float texID;
		};

		class Renderable2D
		{
		protected:
			math::Vector3f m_position;
			math::Vector2f m_size;
			unsigned int m_color;
			std::vector<math::Vector2f> m_texCoord;
			Texture* m_texture;

		protected:
			Renderable2D() : m_texture(nullptr) { setTexCoordDefaults(); }
		public:
			Renderable2D(math::Vector3f position, math::Vector2f size, unsigned int color)
				: m_position(position), m_size(size), m_color(color), m_texture(nullptr) { setTexCoordDefaults(); }

			virtual ~Renderable2D() {}

			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			}

			void setColor(const math::Vector4f& color) 
			{
				const int r = (int)(color.x * 255);
				const int g = (int)(color.y * 255);
				const int b = (int)(color.z * 255);
				const int a = (int)(color.w * 255);
				m_color = a << 24 | b << 16 | g << 8 | r;
			}
			inline void setColor(const unsigned int color) { m_color = color; }
			inline const math::Vector3f& getPosition()	const { return m_position;	}
			inline const math::Vector2f& getSize()		const { return m_size;		}
			inline const unsigned int& getColor()		const { return m_color;		}
			inline const std::vector<seng::math::Vector2f> &getTexCoord() const { return m_texCoord; }
			inline const GLuint getTID() const { return m_texture == nullptr ? 0 : m_texture->getID();  }
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