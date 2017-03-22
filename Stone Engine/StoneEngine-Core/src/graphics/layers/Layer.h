#pragma once

#include "../rendering/Renderer2D.h"
#include "../rendering/Renderable2D.h"

namespace seng
{
	namespace graphics
	{
		class Layer
		{
		protected:
			Renderer2D* m_renderer;
			std::vector<Renderable2D*> m_renderables;
			Shader* m_shader;
			math::Matrix4f m_projectionMatrix;

		protected:
			Layer(Renderer2D* renderer, Shader* shader, math::Matrix4f projectionMatrix);
		public:
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();
		};
	}
}