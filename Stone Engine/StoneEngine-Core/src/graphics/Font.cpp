#include "Font.h"

namespace seng
{
	namespace graphics
	{
		Font::Font(/*const std::string name, */const std::string& path, int size)
			: /*m_name(name), */m_path(m_path), m_size(size)
		{
			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, 32, ("./res/" + path).c_str());//"./res/fonts/SourceSansPro-Regular.otf");
		}
	}
}