#include <iostream>
#include <chrono>

#include "src\graphics\window.h"
#include "src\math\maths.h"
#include "src\resource\ResourceLoader.h"
#include "src\graphics\Shader.h"

int main(int argc, char *args)
{
	using namespace std::chrono;
	using namespace seng::math;
	using namespace seng::graphics;
	using namespace seng::resource;

	
	Window window(800, 600, "Stone Engine - Test");
	std::cout << window.getVersion() << std::endl;
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);


	GLfloat vertices[] = 
	{
		-1, -1,  0,
		-1,  1,  0,
		 1,  1,  0,
		-1, -1,  0,
		 1,  1,  0,
		 1, -1,  0
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	Matrix4f ortho = Matrix4f::orthopgraphic(-2, 2, -2, 2, -1.0, 1.0);

	Shader shader("./res/basic.vs", "./res/basic.fs");
	shader.enable();

	shader.setUniformMat4f("pr_matrix", ortho);
	shader.setUniform2f("lightPos", Vector2f(0.4f, 0.2f));
	shader.setUniform4f("colour", Vector4f(0.2f, 0.5f, 0.8f, 1.0f));


	int frameCounter = 0;
	steady_clock::time_point timeSinceStart = high_resolution_clock::now();

	float x = 0;

	while (!window.closed())
	{
		window.clear();

		shader.setUniformMat4f("ml_matrix", Matrix4f::rotation(x += 0.01, Vector3f(0, 0, 1)));
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
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