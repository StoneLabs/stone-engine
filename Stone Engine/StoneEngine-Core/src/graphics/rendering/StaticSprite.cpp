#include "..\buffers\Buffer.h"
#include "..\buffers\IndexBuffer.h"
#include "..\buffers\VertexArray.h"
#include "..\Shader.h"
#include "..\..\math\maths.h"
#include "Renderable2D.h"
#include "StaticSprite.h"

namespace seng
{
	namespace graphics
	{
		StaticSprite::StaticSprite(float x, float y, float width, float height,
			const math::Vector4f &color, Shader &shader)
			: Renderable2D(math::Vector3f(x,y,0), math::Vector2f(width, height), 0xffff00ff), m_shader(shader)
		{
			m_vertexArray = new VertexArray();
			GLfloat vertices[] = { 0, 0, 0, 0, height, 0, width, height, 0, width, 0, 0 };
			GLfloat colors[] = { color.x, color.y, color.z, color.w, color.x, color.y, color.z, color.w, color.x, color.y, color.z, color.w, color.x, color.y, color.z, color.w, };

			m_vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			m_vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

			GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
			m_indexBuffer = new IndexBuffer(indices, 6);
		}

		StaticSprite::~StaticSprite()
		{
			delete m_vertexArray;
			delete m_indexBuffer;
		}
	}
}