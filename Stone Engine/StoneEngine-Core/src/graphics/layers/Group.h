#pragma once

#include <vector>
#include "../rendering/Renderable2D.h"

namespace seng
{
	namespace graphics
	{
		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> m_renderables;
			math::Matrix4f m_transformation;

		public:
			Group(const math::Matrix4f& transform);
			~Group();
			void submit(Renderer2D* renderer) const override;
			void add(Renderable2D* renderable);
		};
	}
}