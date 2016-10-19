#pragma once

#include "Renderer2D.h"
#include "..\buffers\IndexBuffer.h"

namespace seng
{
	namespace graphics
	{
#define BATCHRENDERER_MAX_SPRITES	60000
#define BATCHRENDERER_VERTEX_SIZE	sizeof(VertexData)
#define BATCHRENDERER_SPRITE_SIZE	BATCHRENDERER_VERTEX_SIZE * 4
#define BATCHRENDERER_BUFFER_SIZE	BATCHRENDERER_SPRITE_SIZE * BATCHRENDERER_MAX_SPRITES
#define BATCHRENDERER_INDICES_SIZE	BATCHRENDERER_MAX_SPRITES * 6

#define BATCHRENDERER_SHADER_VERTEX_INDEX	0
#define BATCHRENDERER_SHADER_COLOR_INDEX	1

		class BatchRenderer2D : Renderer2D
		{
		private:
			GLuint m_VAO;
			GLuint m_VBO;
			IndexBuffer *m_IBO;
			GLsizei m_indexCount;
			VertexData *m_buffer;

		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void begin();
			void end();
			void submit(const Renderable2D *renderable) override;
			void flush() override;

		private:
			void init();
		};
	}
}