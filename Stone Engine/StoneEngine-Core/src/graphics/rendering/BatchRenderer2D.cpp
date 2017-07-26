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
			const unsigned int color = renderable->getColor();
			const std::vector<Vector2f> &texCoord = renderable->getTexCoord();
			const GLuint tid = renderable->getTID();

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

			m_buffer->vertex = *m_transformationBack * position;
			m_buffer->texCoord = texCoord[0];
			m_buffer->texID = tslot;
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = *m_transformationBack * Vector3f(position.x, position.y + size.y, position.z);
			m_buffer->texCoord = texCoord[1];
			m_buffer->texID = tslot;
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = *m_transformationBack * Vector3f(position.x + size.x, position.y + size.y, position.z);
			m_buffer->texCoord = texCoord[2];
			m_buffer->texID = tslot;
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = *m_transformationBack * Vector3f(position.x + size.x, position.y, position.z);
			m_buffer->texCoord = texCoord[3];
			m_buffer->texID = tslot;
			m_buffer->color = color;
			m_buffer++;

			m_indexCount += 6;

		}

		void BatchRenderer2D::drawString(const std::string& text, const math::Vector3f position, const Font& font, const unsigned int color)
		{
			using namespace ftgl;
			using namespace math;
			
			float tslot = 0.0f;
			bool found = false;
			for (int i = 0; i < m_textureSlots.size(); i++)
			{
				if (m_textureSlots[i] == font.getID())
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
				m_textureSlots.push_back(font.getID());
				tslot = (float)(m_textureSlots.size() - 1 + 1);
			}

			float scaleX = 960.0f / 32.0f, scaleY = 640.0f / 18.0f;
			float x = position.x;

			for (int i = 0; i < text.length(); i++)
			{
				texture_glyph_t* glyph = ftgl::texture_font_get_glyph(font.getFTGLFont(), text[i]);
				if (glyph != NULL)
				{
					if (i > 0)
					{
						float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
						x += kerning / scaleX;
					}

					//position
					float x0 = x + glyph->offset_x / scaleX;
					float y0 = position.y + glyph->offset_y / scaleY;
					float x1 = x0 + glyph->width / scaleX;
					float y1 = y0 - glyph->height / scaleY;

					//tex coordinates
					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;
				
					m_buffer->vertex = *m_transformationBack * Vector3f(x0, y0, 0);
					m_buffer->texCoord = Vector2f(u0,v0);
					m_buffer->texID = tslot;
					m_buffer->color = color;
					m_buffer++;

					m_buffer->vertex = *m_transformationBack * Vector3f(x0, y1, 0);
					m_buffer->texCoord = Vector2f(u0, v1);
					m_buffer->texID = tslot;
					m_buffer->color = color;
					m_buffer++;

					m_buffer->vertex = *m_transformationBack * Vector3f(x1, y1, 0);
					m_buffer->texCoord = Vector2f(u1, v1);
					m_buffer->texID = tslot;
					m_buffer->color = color;
					m_buffer++;

					m_buffer->vertex = *m_transformationBack * Vector3f(x1, y0, 0);
					m_buffer->texCoord = Vector2f(u1, v0);
					m_buffer->texID = tslot;
					m_buffer->color = color;
					m_buffer++;

					m_indexCount += 6;

					x += glyph->advance_x / scaleX;
				}
			}
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