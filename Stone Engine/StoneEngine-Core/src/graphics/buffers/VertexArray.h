#pragma once

#include "Buffer.h"
#include <vector>
#include <glew.h>

namespace seng
{
	namespace graphics
	{
		class VertexArray
		{
		private:
			GLuint m_arrayID;
			std::vector<Buffer*> m_buffers;

		public:
			VertexArray();
			~VertexArray();

			void addBuffer(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;
		};
	}
}