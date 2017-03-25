#pragma once

#include "../../resource/ResourceLoader.h"
#include <string.h>
#include <glew.h>
#include <FreeImage.h>
#include <iostream>

namespace seng
{
	namespace graphics
	{
		class Texture
		{
		private:
			std::string m_filename;
			GLuint m_tid;
			GLsizei m_width, m_height;

		public:
			Texture(const std::string &filename);
			~Texture();

			void bind() const;
			void unbind() const;

			inline const unsigned int getWidth() const { return m_width; }
			inline const unsigned int getHeight() const { return m_height; }

		private:
			GLuint load();
		};
	}
}