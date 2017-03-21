#pragma once

#include <glew.h>
#include "..\..\math\maths.h"
#include "Renderable2D.h"

namespace seng
{
	namespace graphics
	{
		class Renderer2D
		{
		protected:
			std::vector<math::Matrix4f> m_transformationStack;
			const math::Matrix4f *m_transformationBack;

		protected:
			Renderer2D() 
			{
				m_transformationStack.push_back(math::Matrix4f::identity()); 
				m_transformationBack = &m_transformationStack.back();
			 }
		public:
			void push(math::Matrix4f matrix, bool override = false)
			{
				if (override)
					m_transformationStack.push_back(matrix);
				else
					m_transformationStack.push_back(m_transformationStack.back() * matrix);

				m_transformationBack = &m_transformationStack.back();
			}
			void pop() 
			{
				if (m_transformationStack.size() > 1) m_transformationStack.pop_back(); /* TODO log error */
				m_transformationBack = &m_transformationStack.back();
			}
			virtual void submit(const Renderable2D *renderable) = 0;
			virtual void flush() = 0;
			virtual void begin() {};
			virtual void end() {};
		};
	}
}