#include "src/utils/timer.h"

#include "src/graphics/buffers/Buffer.h"
#include "src/graphics/buffers/IndexBuffer.h"
#include "src/graphics/buffers/VertexArray.h"

#include "src/graphics/layers/Group.h"
#include "src/graphics/layers/TileLayer.h"

#include "src/graphics/rendering/BatchRenderer2D.h"
#include "src/graphics/rendering/Renderable2D.h"
#include "src/graphics/rendering/Renderer2D.h"
#include "src/graphics/rendering/SimpleRenderer2D.h"
#include "src/graphics/rendering/Sprite.h"
#include "src/graphics/rendering/StaticSprite.h"
#include "src/graphics/rendering/Texture.h"

#include "src/graphics/Shader.h"
#include "src/graphics/window.h"

#include "src/math/maths.h"
#include "src/resource/ResourceLoader.h"

#include <chrono>
#include <iostream>
#include <vector>

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WIN32 or WIN64
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

int main(int argc, char *args)
{

	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return errno;
	}

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

	std::cout << "The current working directory is " << cCurrentPath << std::endl;

	using namespace std;
	using namespace std::chrono;

	using namespace seng;
	using namespace seng::math;
	using namespace seng::graphics;
	using namespace seng::resource;

	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Stone Engine - Test");
	std::cout << window.getVersion() << std::endl << std::endl;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Shader* sceneShader = new Shader("./res/basic.vs", "./res/basic.fs");
	TileLayer scene(sceneShader);

	Texture *textures[] = {
		new Texture("./res/test1.png"),
		new Texture("./res/test2.png"),
		new Texture("./res/test3.png")
	};

#pragma region Sprites
	for (float y = -9.0f; y < 9.0f; y ++)
	{
		for (float x = -16.0f; x < 16.0f; x ++)
		{
			if (rand() % 4 == 0)
				scene.add(new Sprite(x, y, 0.9f, 0.9f, Vector4f(rand() % 1000 / 1000.0f, 0, 1, 1)));
			else
				scene.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
	}
#pragma endregion Being generated

	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	sceneShader->enable();
	sceneShader->setUniform1iv("textures", texIDs, 10);

	double MouseX = window.getWidth() / 2, MouseY = window.getHeight() / 2;
	Timer time;
	float timer = 0;
	unsigned short frames = 0;
	while (!window.closed())
	{
		window.clear();

		if (window.isMouseButtonPressed(0))
			window.getCursorPosition(MouseX, MouseY);

		scene.render();
		sceneShader->setUniform2f("lightPos", Vector2f((float)MouseX / WINDOW_WIDTH * 2 - 1, -((float)MouseY / WINDOW_HEIGHT * 2 - 1)));
		
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