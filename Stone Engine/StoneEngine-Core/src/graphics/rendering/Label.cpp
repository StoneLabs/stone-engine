#include "Label.h"

namespace seng
{
	namespace graphics
	{
		Label::Label(std::string text, float x, float y, math::Vector4f color)
			: Renderable2D(math::Vector3f(x, y, 0.0f), math::Vector2f(x, y), color), m_Text(text)
		{

		}

		void Label::submit(Renderer2D* renderer) const
		{
			renderer->drawString(m_Text, m_position, m_color);
		}
	}
}