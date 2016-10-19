#pragma once

#include <deque>
#include "StaticSprite.h"
#include "Renderer2D.h"

namespace seng
{
	namespace graphics
	{
		class SimpleRenderer2D : Renderer2D
		{
		private:
			std::deque<const StaticSprite*> m_renderQueue;

		public:
			void submit(const Renderable2D *renderable) override;
			void flush() override;
		};
	}
}