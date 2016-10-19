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
		class StaticSprite : public Renderable2D
		{
		private:
			VertexArray *m_vertexArray;
			IndexBuffer *m_indexBuffer;
			Shader &m_shader;

		public:
			StaticSprite(float x, float y, float width, float height,
				const math::Vector4f &color, Shader &shader);

			~StaticSprite();

			inline const VertexArray* getVAO()	const { return m_vertexArray; }
			inline const IndexBuffer* getIBO()	const { return m_indexBuffer; }
			inline Shader& getShader()			const { return m_shader; }
		};
	}
}