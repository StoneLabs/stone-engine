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
#include "src/graphics/rendering/simple2Drenderer.h"

int main(int argc, char *args)
{
	using namespace std::chrono;
	using namespace seng::math;
	using namespace seng::graphics;
	using namespace seng::resource;

	Window window(800, 600, "Stone Engine - Test");
	std::cout << window.getVersion() << std::endl;
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

	Matrix4f ortho = Matrix4f::orthopgraphic(-2, 2, -2, 2, -1.0, 1.0);

	Shader shader("./res/basic.vs", "./res/basic.fs");
	shader.enable();
	shader.setUniformMat4f("pr_matrix", ortho);

	Renderable2D sprite1(Vector3f(-1, 0, 0), Vector2f(2, 2.0f), Vector4f(1, 0, 0, 1), shader);
	Renderable2D sprite2(Vector3f(0, -2, 0), Vector2f(1, 1.5f), Vector4f(0, 0, 1, 1), shader);
	Simple2DRenderer renderer;

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
		
		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
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