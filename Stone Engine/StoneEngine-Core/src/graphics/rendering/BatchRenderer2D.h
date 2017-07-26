#pragma once

#include <cstddef>
#include "Renderer2D.h"
#include "Renderable2D.h"
#include "..\buffers\IndexBuffer.h"
#include "../../math/maths.h"

#include "../../../ext/freetype-gl/freetype-gl.h"

namespace seng
{
	namespace graphics
	{
#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX		0
#define SHADER_COLOR_INDEX		1
#define SHADER_TEXCOORD_INDEX	2
#define SHADER_TEXID_INDEX		3

		class BatchRenderer2D : public Renderer2D
		{
		private:
			GLuint m_VAO;
			GLuint m_VBO;
			IndexBuffer *m_IBO;
			GLsizei m_indexCount;
			VertexData *m_buffer;
			std::vector<GLuint> m_textureSlots;
			ftgl::texture_atlas_t* m_FTAtlas;
			ftgl::texture_font_t* m_FTFont;

		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void begin() override;
			void end() override;
			void submit(const Renderable2D *renderable) override;
			void drawString(const std::string& text, const math::Vector3f position, const unsigned int color) override;
			void flush() override;

		private:
			void init();
		};
	}
}