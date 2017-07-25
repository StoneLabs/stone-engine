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
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glEnableVertexAttribArray(SHADER_TEXCOORD_INDEX);
			glEnableVertexAttribArray(SHADER_TEXID_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
			glVertexAttribPointer(SHADER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::texCoord)));
			glVertexAttribPointer(SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::texID)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
			{
				indices[  i  ] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);

			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 1);
			m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, 80, "./res/arial.ttf");

			for (int i = 32; i <= 122; i++)
				ftgl::texture_font_get_glyph(m_FTFont, (char)i);
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
			const std::vector<Vector2f> &texCoord = renderable->getTexCoord();
			const GLuint tid = renderable->getTID();

			unsigned int c = 0;

			float tslot = 0.0f;
			if (tid > 0)
			{
				bool found = false;
				for (int i = 0; i < m_textureSlots.size(); i++)
				{
					if (m_textureSlots[i] == tid)
					{
						tslot = (float)(i+1);
						found = true;
						break;
					}
				}

				if (!found)
				{
					if (m_textureSlots.size() >= 32)
					{
						end();
						flush();
						begin();
					}
					m_textureSlots.push_back(tid);
					tslot = (float)(m_textureSlots.size() - 1 + 1);
				}
			}
			else
			{
				int r = (int)(color.x * 255);
				int g = (int)(color.y * 255);
				int b = (int)(color.z * 255);
				int a = (int)(color.w * 255);
				c = a << 24 | b << 16 | g << 8 | r;
			}

			m_buffer->vertex = *m_transformationBack * position;
			m_buffer->texCoord = texCoord[0];
			m_buffer->texID = tslot;
			m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = *m_transformationBack * Vector3f(position.x, position.y + size.y, position.z);
			m_buffer->texCoord = texCoord[1];
			m_buffer->texID = tslot;
			m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = *m_transformationBack * Vector3f(position.x + size.x, position.y + size.y, position.z);
			m_buffer->texCoord = texCoord[2];
			m_buffer->texID = tslot;
			m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = *m_transformationBack * Vector3f(position.x + size.x, position.y, position.z);
			m_buffer->texCoord = texCoord[3];
			m_buffer->texID = tslot;
			m_buffer->color = c;
			m_buffer++;

			m_indexCount += 6;

		}

		void BatchRenderer2D::drawString(const std::string& text, const math::Vector3f position, const math::Vector4f color)
		{
			using namespace ftgl;
			using namespace math;

			float tslot = 0.0f;
			bool found = false;
			for (int i = 0; i < m_textureSlots.size(); i++)
			{
				if (m_textureSlots[i] == m_FTAtlas->id)
				{
					tslot = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (m_textureSlots.size() >= 32)
				{
					end();
					flush();
					begin();
				}
				m_textureSlots.push_back(m_FTAtlas->id);
				tslot = (float)(m_textureSlots.size() - 1 + 1);
			}


			m_buffer->vertex = Vector3f(-8, -8, 0);
			m_buffer->texCoord = Vector2f(0, 1);
			m_buffer->texID = tslot;
			//m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = Vector3f(-8, 8, 0);
			m_buffer->texCoord = Vector2f(0, 0);
			m_buffer->texID = tslot;
			//m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = Vector3f(8, 8, 0);
			m_buffer->texCoord = Vector2f(1, 0);
			m_buffer->texID = tslot;
			//m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = Vector3f(8, -8, 0);
			m_buffer->texCoord = Vector2f(1, 1);
			m_buffer->texID = tslot;
			//m_buffer->color = c;
			m_buffer++;

			m_indexCount += 6;
		}

		void BatchRenderer2D::flush()
		{
			for (int i = 0; i < m_textureSlots.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
			}

			glBindVertexArray(m_VAO);
			m_IBO->bind();

			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

			m_IBO->unbind();
			glBindVertexArray(0);

			m_indexCount = 0;
		}
	}
}