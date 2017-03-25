#include "Texture.h"

namespace seng
{
	namespace graphics
	{
		Texture::Texture(const std::string &filename)
			: m_filename(filename)
		{
			m_tid = load();
		}

		Texture::~Texture()
		{

		}

		GLuint Texture::load()
		{
			BYTE* pixels = seng::resource::ResourceLoader::loadImage(m_filename.c_str(), &m_width, &m_height);

			GLuint result;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			return result;
		}

		void Texture::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, m_tid);
		}

		void Texture::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}