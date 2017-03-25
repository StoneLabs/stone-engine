#include "Group.h"

namespace seng
{
	namespace graphics
	{
		Group::Group(const math::Matrix4f& transformation)
			: m_transformation(transformation)
		{

		}

		void Group::submit(Renderer2D* renderer) const
		{
			renderer->push(m_transformation);

			for (const Renderable2D* renderable : m_renderables)
				renderable->submit(renderer);

			renderer->pop();
		}

		void Group::add(Renderable2D* renderable)
		{
			m_renderables.push_back(renderable);
		}
	}
}