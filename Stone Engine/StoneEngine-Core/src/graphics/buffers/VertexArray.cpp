#include "VertexArray.h"


namespace seng
{
	namespace graphics
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_arrayID);
		}

		VertexArray::~VertexArray()
		{
			for (int i = 0; i < m_buffers.size(); i++)
				delete m_buffers[i];

			glDeleteVertexArrays(1, &m_arrayID);
		}

		void VertexArray::addBuffer(Buffer* buffer, GLuint index)
		{
			bind();
			buffer->bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, false, 0, 0);

			buffer->unbind();
			unbind();
		}

		void VertexArray::bind() const
		{
			glBindVertexArray(m_arrayID);
		}

		void VertexArray::unbind() const
		{
			glBindVertexArray(0);
		}
	}
}