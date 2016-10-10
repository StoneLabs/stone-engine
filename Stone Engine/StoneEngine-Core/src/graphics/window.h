#pragma once
#include <glew.h>
#include <glfw3.h>

namespace seng 
{ 
	namespace graphics
	{
		class Window
		{
		private:
			int m_width, m_height;
			const char *m_title;
			GLFWwindow *m_window;

		public:
			Window(int width, int height, const char *name);
			~Window();

			void clear() const;
			void update();

			bool closed() const;
			inline int getWidth() const { return m_width; }
			inline int getHeight() const { return m_height; }


			static inline char* getVersion() { return (char*)glGetString(GL_VERSION); }

		private:
			bool init();
		};
	}
}