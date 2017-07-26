#pragma once

#include <string>
#include "../../../ext/freetype-gl/freetype-gl.h"

namespace seng
{
	namespace graphics
	{
		class Font
		{
		private:
			ftgl::texture_atlas_t* m_FTAtlas;
			ftgl::texture_font_t* m_FTFont;
			const unsigned int m_size;

			//std::string m_name;
			std::string m_path;

		public:
			Font(/*const std::string name, */const std::string& path, int size);

			inline ftgl::texture_font_t *getFTGLFont() const { return m_FTFont; }
			inline const unsigned int getSize() const { return m_size; }
			//inline const std::string& getName() const { return m_name; }
			inline const std::string& getFileName() const { return m_path; }
			inline const unsigned int getID() const { return m_FTAtlas->id; }
		};
	}
}