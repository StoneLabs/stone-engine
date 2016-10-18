#pragma once

#include <glew.h>

namespace seng
{
	namespace graphics
	{
		class Buffer
		{
		private:
			GLuint m_bufferID;
			GLuint m_componentCount;

		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);

			void bind() const;
			void unbind() const;

			inline GLuint getComponentCount() const { return m_componentCount; }
		};
	}
}