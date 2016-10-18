#include "simple2Drenderer.h"

namespace seng
{
	namespace graphics
	{
		void Simple2DRenderer::submit(const Renderable2D *renderable)
		{
			m_renderQueue.push_back(renderable);
		}

		void Simple2DRenderer::flush()
		{
			while (!m_renderQueue.empty())
			{
				const Renderable2D *renderable = m_renderQueue.front();
				renderable->getVAO()->bind();
				renderable->getIBO()->bind();

				renderable->getShader().setUniformMat4f("ml_matrix", math::Matrix4f::translation(renderable->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				renderable->getIBO()->unbind();
				renderable->getVAO()->unbind();

				m_renderQueue.pop_front();
			}
		}
	}
}