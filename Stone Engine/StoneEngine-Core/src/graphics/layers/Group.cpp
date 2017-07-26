#include "Group.h"

namespace seng
{
	namespace graphics
	{
		Group::Group(const math::Matrix4f& transformation)
			: m_transformation(transformation)
		{

		}

		Group::~Group()
		{
			for (int i = 0; i < m_renderables.size(); i++)
				delete m_renderables[i];
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