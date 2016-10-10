#include <iostream>
#include <chrono>

#include "src\graphics\window.h"
#include "src\math\math.h"

int main(int argc, char *args)
{
	using namespace std::chrono;
	using namespace seng::math;
	using namespace seng::graphics;

	Window window(800, 600, "Stone Engine - Test");
	std::cout << window.getVersion() << std::endl;
	
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

	int frameCounter = 0;
	steady_clock::time_point timeSinceStart = high_resolution_clock::now();

	while (!window.closed())
	{
		window.clear();

		if (window.isKeyPressed(GLFW_KEY_A)) std::cout << "Yop!" << std::endl;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) std::cout << "Yea!" << std::endl;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) std::cout << "(" << window.getCursorPositionX() << " | " << window.getCursorPositionY() << ")" << std::endl;



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