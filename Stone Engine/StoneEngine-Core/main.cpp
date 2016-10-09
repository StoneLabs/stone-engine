#include <iostream>

#include "src\graphics\window.h"

int main(int argc, char *args)
{
	using namespace seng;
	using namespace graphics;

	Window window(800, 600, "Stone Engine - Test");
	std::cout << Window::getVersion() << std::endl;

	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

	while (!window.closed())
	{
		window.clear();

		std::cout << window.getWidth() << "," << window.getHeight() << std::endl;

		glBegin(GL_QUADS);

		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f,  0.5f);
		glVertex2f( 0.5f,  0.5f);
		glVertex2f( 0.5f, -0.5f);

		glEnd();

		window.update();
	}

	return 0;
}