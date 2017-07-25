#pragma once

#include "Renderable2D.h"
#include "..\..\math\maths.h"

namespace seng
{
	namespace graphics
	{
		class Label : public Renderable2D
		{
			std::string m_Text;

		public:
			Label(std::string text, float x, float y, math::Vector4f color);
			void submit(Renderer2D* renderer) const override;


		};
	}
}