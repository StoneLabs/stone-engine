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
		class Renderable2D
		{
		protected:
			math::Vector3f m_position;
			math::Vector2f m_size;
			math::Vector4f m_color;

			VertexArray *m_vertexArray;
			IndexBuffer *m_indexBuffer;
			Shader &m_shader;

		public:
			Renderable2D(math::Vector3f position, math::Vector2f size, math::Vector4f color, Shader &shader)
				: m_position(position), m_size(size), m_color(color), m_shader(shader)
			{
				m_vertexArray = new VertexArray();
				GLfloat vertices[] = { 0, 0, 0, 0, size.y, 0, size.x, size.y, 0, size.x, 0, 0 };
				GLfloat colors[] = { color.x, color.y, color.z, color.w, color.x, color.y, color.z, color.w, color.x, color.y, color.z, color.w, color.x, color.y, color.z, color.w, };

				m_vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
				m_vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

				GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
				m_indexBuffer = new IndexBuffer(indices, 6);
			}

			virtual ~Renderable2D()
			{
				delete m_vertexArray;
				delete m_indexBuffer;
			}

			inline const math::Vector3f& getPosition()	const { return m_position;	}
			inline const math::Vector2f& getSize()		const { return m_size;		}
			inline const math::Vector4f& getColor()		const { return m_color;		}

			inline const VertexArray* getVAO()	const { return m_vertexArray; }
			inline const IndexBuffer* getIBO()	const { return m_indexBuffer; }
			inline Shader& getShader()			const { return m_shader; }
		};
	}
}