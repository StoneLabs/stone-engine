#include "BatchRenderer2D.h"

namespace seng
{
	namespace graphics
	{
		BatchRenderer2D::BatchRenderer2D()
		{
			init();
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void BatchRenderer2D::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, BATCHRENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(BATCHRENDERER_SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(BATCHRENDERER_SHADER_COLOR_INDEX);

			glVertexAttribPointer(BATCHRENDERER_SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, BATCHRENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(BATCHRENDERER_SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, BATCHRENDERER_VERTEX_SIZE, (const GLvoid*)(3*sizeof(GLfloat)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLushort indices[BATCHRENDERER_INDICES_SIZE];

			int offset = 0;
			for (int i = 0; i < BATCHRENDERER_INDICES_SIZE; i+=6)
			{
				indices[  i  ] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;
				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			m_IBO = new IndexBuffer(indices, BATCHRENDERER_INDICES_SIZE);

			glBindVertexArray(0);
		}

		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::submit(const Renderable2D *renderable)
		{
			using namespace math;

			const Vector3f &position = renderable->getPosition();
			const Vector2f &size = renderable->getSize();
			const Vector4f &color = renderable->getColor();

			m_buffer->vertex = position;
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = Vector3f(position.x, position.y + size.y, position.z);
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = Vector3f(position.x + size.x, position.y + size.y, position.z);
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = Vector3f(position.x + size.x, position.y, position.z);
			m_buffer->color = color;
			m_buffer++;

			m_indexCount += 6;

		}

		void BatchRenderer2D::flush()
		{
			glBindVertexArray(m_VAO);
			m_IBO->bind();

			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, NULL);

			m_IBO->unbind();
			glBindVertexArray(0);

			m_indexCount = 0;
		}
	}
}