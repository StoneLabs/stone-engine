#include "Label.h"

namespace seng
{
	namespace graphics
	{
		Label::Label(std::string text, float x, float y, const unsigned int color)
			: Renderable2D(math::Vector3f(x, y, 0.0f), math::Vector2f(x, y), color), text(text)
		{

		}

		void Label::submit(Renderer2D* renderer) const
		{
			renderer->drawString(text, m_position, m_color);
		}
	}
}