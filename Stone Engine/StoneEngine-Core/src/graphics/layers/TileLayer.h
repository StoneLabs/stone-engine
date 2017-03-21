#pragma once

#include "../rendering/Renderer2D.h"
#include "../rendering/Renderable2D.h"
#include "../rendering/BatchRenderer2D.h"
#include "Layer.h"

namespace seng
{
	namespace graphics
	{
		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader* shader);
			~TileLayer();
		};
	}
}