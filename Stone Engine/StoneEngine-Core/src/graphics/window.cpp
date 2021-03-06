#include <iostream>
#include "window.h"

namespace seng
{
	namespace graphics
	{
		bool Window::m_keys[MAX_KEYS];
		bool Window::m_mouseButtons[MAX_MOUSE_BUTTONS];
		bool Window::m_keys_prev[MAX_KEYS];
		bool Window::m_mouseButtons_prev[MAX_MOUSE_BUTTONS];
		double Window::mx, Window::my;

		Window::Window(int width, int height, const char *name)
		{
			m_title		= name;
			m_width		= width;
			m_height	= height;

			if (!init())
				glfwTerminate();

			for (int i = 0; i < MAX_KEYS; i++)
				m_keys[i] = false;
			for (int i = 0; i < MAX_KEYS; i++)
				m_keys_prev[i] = false;
			for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
				m_mouseButtons[i] = false;
			for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
				m_mouseButtons_prev[i] = false;
 
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
			glfwSetWindowUserPointer(m_window, this);
			glfwSetFramebufferSizeCallback(m_window, window_resize);
			glfwSetKeyCallback(m_window, key_callback);
			glfwSetMouseButtonCallback(m_window, mouse_button_callback);
			glfwSetCursorPosCallback(m_window, mouse_cursor_position_callback);
			glfwSwapInterval(0); //Disable V-Sync

			if (glewInit() != GLEW_OK) //Init after context creation!
			{
				std::cout << "Could not initialize glew!" << std::endl;
				return false;
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			return true;
		}

		void Window::clear() const 
		{ 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		}

		void Window::update()
		{
			memcpy(m_keys_prev, m_keys, MAX_KEYS * sizeof(bool));
			memcpy(m_mouseButtons_prev, m_mouseButtons, MAX_MOUSE_BUTTONS * sizeof(bool));

			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;

			glfwPollEvents();

			glfwGetFramebufferSize(m_window, &m_width, &m_height);

			glfwSwapBuffers(m_window);
		}

		bool Window::closed() const { return glfwWindowShouldClose(m_window) == 1; }

		void window_resize(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->m_width = width;
			win->m_height = height;
		}

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			
			win->m_keys[key] = action != GLFW_RELEASE;
		}
		void mouse_button_callback(GLFWwindow *window, int button, int action, int mode)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);

			win->m_mouseButtons[button] = action != GLFW_RELEASE;
		}
		void mouse_cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);

			win->mx = xpos;
			win->my = ypos;
		}

		bool Window::isKeyDown(unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;

			return m_keys[keycode];
		}
		bool Window::isKeyPressed(unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;

			return m_keys[keycode] && !m_keys_prev[keycode];
		}
		bool Window::isKeyReleased(unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;

			return !m_keys[keycode] && m_keys_prev[keycode];
		}

		bool Window::isMouseButtonDown(unsigned int button) const
		{
			if (button >= MAX_MOUSE_BUTTONS)
				return false;

			return m_mouseButtons[button];
		}
		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			if (button >= MAX_MOUSE_BUTTONS)
				return false;

			return m_mouseButtons[button] && !m_mouseButtons_prev[button];
		}
		bool Window::isMouseButtonReleased(unsigned int button) const
		{
			if (button >= MAX_MOUSE_BUTTONS)
				return false;

			return !m_mouseButtons[button] && m_mouseButtons_prev[button];
		}

		double Window::getCursorPositionX() const
		{
			return mx;
		}
		double Window::getCursorPositionY() const
		{
			return my;
		}
		void Window::getCursorPosition(double &x, double &y) const
		{
			x = mx;
			y = my;
		}
	}
}