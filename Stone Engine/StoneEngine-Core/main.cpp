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

#include <time.h>
#include <vector>

#define BATCH_RENDERER 1

#define X_RESOLUTION 120.0f
#define Y_RESOLUTION 120.0f
#define XDISTANCE 0.005f
#define YDISTANCE 0.005f

#if BATCH_RENDERER
#define SPRITE_TYPE Sprite
#define RENDERER_TYPE BatchRenderer2D
#define RENDERER_TYPES "BatchRenderer2D"
#define SHADER_ADDITION
#define RENDERER_BEGIN renderer.begin();
#define RENDERER_END renderer.end();
#else
#define SPRITE_TYPE StaticSprite
#define RENDERER_TYPE SimpleRenderer2D
#define RENDERER_TYPES "SimpleRenderer2D"
#define SHADER_ADDITION , shader
#define RENDERER_BEGIN 
#define RENDERER_END 
#endif


int main(int argc, char *args)
{
	using namespace std;
	using namespace std::chrono;
	using namespace seng::math;
	using namespace seng::graphics;
	using namespace seng::resource;

	Window window(800, 600, "Stone Engine - Test");
	std::cout << window.getVersion() << std::endl;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Matrix4f ortho = Matrix4f::orthopgraphic(-2, 2, -2, 2, -1.0, 1.0);

	Shader shader("./res/basic.vs", "./res/basic.fs");
	shader.enable();
	shader.setUniformMat4f("pr_matrix", ortho);

	vector<SPRITE_TYPE*> sprites;
	srand(time(NULL));

	for (float x = -2; x < 2; x += 4 / X_RESOLUTION)
		for (float y = -2; y < 2; y += 4 / Y_RESOLUTION)
		{
			sprites.push_back(
				new SPRITE_TYPE(x, y, (4 / X_RESOLUTION - XDISTANCE), (4 / Y_RESOLUTION - YDISTANCE),
					Vector4f(rand() % 1000 / 1000.0f, 0.1f, 1, 1) SHADER_ADDITION)
				);
		}

	RENDERER_TYPE renderer;

	std::cout << "Rendering " << sprites.size() << " sprites using the " << RENDERER_TYPES << std::endl;
	std::cout << "X-Offset: " << 4 / X_RESOLUTION << std::endl;
	std::cout << "X-Width:  " << 4 / X_RESOLUTION - XDISTANCE << std::endl;
	std::cout << "Y-Offset: " << 4 / Y_RESOLUTION << std::endl;
	std::cout << "Y-Width:  " << 4 / Y_RESOLUTION - YDISTANCE << std::endl;
	
	int frameCounter = 0;
	steady_clock::time_point timeSinceStart = high_resolution_clock::now();

	float x = 0;
	double MouseX = window.getWidth()/2, MouseY = window.getHeight()/2;

	while (!window.closed())
	{
		window.clear();

		if (window.isMouseButtonPressed(0))
			window.getCursorPosition(MouseX, MouseY);

		shader.setUniform2f("lightPos", Vector2f(MouseX / window.getWidth() * 2 - 1, -(MouseY / window.getHeight() * 2 - 1)));
		
		RENDERER_BEGIN
		for (int i = 0; i < sprites.size(); i++)
		{
			renderer.submit(sprites[i]);
		}
		RENDERER_END
		renderer.flush();
		
		window.update();

		frameCounter++;
		if ((high_resolution_clock::now() - timeSinceStart).count() > 1000000000)
		{
			std::cout << "FPS: " << frameCounter << std::endl;
			timeSinceStart = high_resolution_clock::now();
			frameCounter = 0;
		}
	}

	return 0;
}