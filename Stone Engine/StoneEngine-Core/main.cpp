#include <iostream>
#include <chrono>

#include "src\graphics\window.h"
#include "src\math\maths.h"
#include "src\resource\ResourceLoader.h"
#include "src\graphics\Shader.h"

#include "src/graphics/buffers/Buffer.h"
#include "src/graphics/buffers/IndexBuffer.h"
#include "src/graphics/buffers/VertexArray.h"

#include "src/graphics/rendering/Renderer2D.h"
#include "src/graphics/rendering/Renderable2D.h"
#include "src/graphics/rendering/SimpleRenderer2D.h"
#include "src/graphics/rendering/StaticSprite.h"
#include "src/graphics/rendering/Sprite.h"
#include "src/graphics/rendering/BatchRenderer2D.h"

#include "src/graphics/layers/TileLayer.h"

#include "src/utils/timer.h"

#include <vector>

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

#define BATCH_RENDERER 1

#if BATCH_RENDERER
#define RENDERER_TYPES "BatchRenderer2D"
#else
#define RENDERER_TYPES "SimpleRenderer2D"
#endif


int main(int argc, char *args)
{
	using namespace std;
	using namespace std::chrono;
	using namespace seng;
	using namespace seng::math;
	using namespace seng::graphics;
	using namespace seng::resource;

	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Stone Engine - Test");
	std::cout << window.getVersion() << std::endl;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Shader* shader = new Shader("./res/basic.vs", "./res/basic.fs");

	TileLayer layer(shader);
	for (float y = -9.0f; y < 9.0f; y += 0.1)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1)
		{
			layer.add(new Sprite(x, y, 0.08f, 0.08f, Vector4f(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}

	double MouseX = window.getWidth()/2, MouseY = window.getHeight()/2;

	Timer time;
	float timer = 0;
	unsigned short frames = 0;
	while (!window.closed())
	{
		window.clear();

		if (window.isMouseButtonPressed(0))
			window.getCursorPosition(MouseX, MouseY);
		shader->setUniform2f("lightPos", Vector2f(MouseX / WINDOW_WIDTH * 2 - 1, -(MouseY / WINDOW_HEIGHT * 2 - 1)));

		layer.render();

		window.update();
		
		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("FPS: %d\n", frames);
			frames = 0;
		}
	}
	
	return 0;
}