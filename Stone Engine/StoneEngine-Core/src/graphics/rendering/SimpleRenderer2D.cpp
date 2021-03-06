#include "simpleRenderer2D.h"

namespace seng
{
	namespace graphics
	{
		void SimpleRenderer2D::submit(const Renderable2D *renderable)
		{
			m_renderQueue.push_back((StaticSprite*)renderable);
		}

		void SimpleRenderer2D::flush()
		{
			while (!m_renderQueue.empty())
			{
				const StaticSprite *sprite = m_renderQueue.front();
				sprite->getVAO()->bind();
				sprite->getIBO()->bind();

				sprite->getShader().setUniformMat4f("ml_matrix", math::Matrix4f::translation(sprite->getPosition()));
				glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				sprite->getIBO()->unbind();
				sprite->getVAO()->unbind();

				m_renderQueue.pop_front();
			}
		}
	}
}