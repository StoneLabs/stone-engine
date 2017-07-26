#include "Label.h"

namespace seng
{
	namespace graphics
	{
		Label::Label(std::string text, float x, float y, Font* font, const unsigned int color)
			: Renderable2D(math::Vector3f(x, y, 0.0f), math::Vector2f(x, y), color), text(text), font(font)
		{

		}

		void Label::submit(Renderer2D* renderer) const
		{
			renderer->drawString(text, m_position, *font, m_color);
		}
	}
}