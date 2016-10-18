#pragma once

#include <deque>
#include "Renderer2D.h"

namespace seng
{
	namespace graphics
	{
		class Simple2DRenderer : Renderer2D
		{
		private:
			std::deque<const Renderable2D*> m_renderQueue;

		public:
			void submit(const Renderable2D *renderable) override;
			void flush() override;
		};
	}
}