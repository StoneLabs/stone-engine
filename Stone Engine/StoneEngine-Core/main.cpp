#include <iostream>
#include <chrono>

#include "src\graphics\window.h"

int main(int argc, char *args)
{
	using namespace seng;
	using namespace graphics;
	using namespace std::chrono;

	Window window(800, 600, "Stone Engine - Test");
	std::cout << Window::getVersion() << std::endl;
	
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

	int frameCounter = 0;
	steady_clock::time_point timeSinceStart = high_resolution_clock::now();

	while (!window.closed())
	{
		window.clear();

		//glBegin(GL_QUADS);

		//glVertex2f(-0.5f, -0.5f);
		//glVertex2f(-0.5f,  0.5f);
		//glVertex2f( 0.5f,  0.5f);
		//glVertex2f( 0.5f, -0.5f);

		//glEnd();

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