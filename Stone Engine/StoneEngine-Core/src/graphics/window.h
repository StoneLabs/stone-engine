#pragma once
#include <glew.h>
#include <glfw3.h>

namespace seng 
{ 
#define MAX_KEYS			1024
#define MAX_MOUSE_BUTTONS	32

	namespace graphics
	{
		class Window
		{
		private:
			int m_width, m_height;
			const char *m_title;
			GLFWwindow *m_window;

			static bool m_keys[MAX_KEYS];
			static bool m_keys_prev[MAX_KEYS];
			static bool m_mouseButtons[MAX_MOUSE_BUTTONS];
			static bool m_mouseButtons_prev[MAX_MOUSE_BUTTONS];
			static double mx, my;

		public:
			Window(int width, int height, const char *name);
			~Window();

			void clear() const;
			void update();

			bool closed() const;
			inline int getWidth() const { return m_width; }
			inline int getHeight() const { return m_height; }

			bool isKeyDown(unsigned int keycode) const;
			bool isKeyPressed(unsigned int keycode) const;
			bool isKeyReleased(unsigned int keycode) const;
			bool isMouseButtonDown(unsigned int button) const;
			bool isMouseButtonPressed(unsigned int button) const;
			bool isMouseButtonReleased(unsigned int button) const;
			void getCursorPosition(double &x, double &y) const;
			double getCursorPositionX() const;
			double getCursorPositionY() const;

			static inline char* getVersion() { return (char*)glGetString(GL_VERSION); }
		private:
			bool init();

			friend static void window_resize(GLFWwindow *window, int width, int height);
			friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
			friend static void mouse_button_callback(GLFWwindow *window, int button, int action, int mode);
			friend static void mouse_cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
		};
	}
}