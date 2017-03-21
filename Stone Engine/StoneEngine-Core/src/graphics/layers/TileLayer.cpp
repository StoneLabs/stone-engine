#include "TileLayer.h"

namespace seng
{
	namespace graphics
	{
		TileLayer::TileLayer(Shader* shader)
			: Layer(new BatchRenderer2D(), shader, math::Matrix4f::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
		{
		}

		TileLayer::~TileLayer()
		{
		}
	}
}