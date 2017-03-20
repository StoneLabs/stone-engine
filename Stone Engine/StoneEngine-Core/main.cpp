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

#include "src/utils/timer.h"

#include <vector>

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

	Window window(960, 540, "Stone Engine - Test");
	std::cout << window.getVersion() << std::endl;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Matrix4f ortho = Matrix4f::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("./res/basic.vs", "./res/basic.fs");
	shader.enable();
	shader.setUniformMat4f("pr_matrix", ortho);

	vector<Renderable2D*> sprites;
	srand(time(NULL));
	
	for (float y = 0; y < 9.0f; y += 0.05)
	{
		for (float x = 0; x < 16.0f; x += 0.05)
		{
#if BATCH_RENDERER
			sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, Vector4f(rand() % 1000 / 1000.0f, 0, 1, 1)));
#else
			sprites.push_back(new StaticSprite(x, y, 0.04f, 0.04f, Vector4f(rand() % 1000 / 1000.0f, 0, 1, 1), shader));
#endif
		}
	}
	int size = sprites.size();


#if BATCH_RENDERER
	BatchRenderer2D renderer;
#else
	SimpleRenderer2D  renderer;
#endif
	std::cout << "Rendering " << size << " sprites using the " << RENDERER_TYPES << std::endl;
	
	float x = 0;
	double MouseX = window.getWidth()/2, MouseY = window.getHeight()/2;

	Timer time;
	float timer = 0;
	unsigned short frames = 0;
	while (!window.closed())
	{
		window.clear();

		if (window.isMouseButtonPressed(0))
			window.getCursorPosition(MouseX, MouseY);

		shader.setUniform2f("lightPos", Vector2f(MouseX / window.getWidth() * 2 - 1, -(MouseY / window.getHeight() * 2 - 1)));

#if BATCH_RENDERER
		renderer.begin();
#endif
		for (int i = 0; i < size; i++)
		{
			renderer.submit(sprites[i]);
		}
#if BATCH_RENDERER
		renderer.end();
#endif
		renderer.flush();
		
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