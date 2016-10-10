#include <iostream>
#include "window.h"

namespace seng
{
	namespace graphics
	{
		void windowResize(GLFWwindow *window, int width, int height);

		Window::Window(int width, int height, const char *name)
		{
			m_title		= name;
			m_width		= width;
			m_height	= height;

			if (!init())
			{
				glfwTerminate();
			}
		}
		Window::~Window() { glfwTerminate(); }
		
		bool Window::init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GLFW!" << std::endl;
				return false;
			}

			m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
			if (!m_window)
			{
				std::cout << "Failed to create GLFW window!" << std::endl;
				return false;
			}

			glfwMakeContextCurrent(m_window);
			glfwSetWindowSizeCallback(m_window, windowResize);

			if (glewInit() != GLEW_OK) //Init after context creation!
			{
				std::cout << "Cound not initialize glew!" << std::endl;
				return false;
			}

			return true;
		}

		void Window::clear() const 
		{ 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		}

		void Window::update()
		{
			glfwPollEvents();

			glfwGetFramebufferSize(m_window, &m_width, &m_height);

			glfwSwapBuffers(m_window);
		}

		bool Window::closed() const { return glfwWindowShouldClose(m_window) == 1; }

		void windowResize(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	}
}