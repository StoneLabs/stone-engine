#pragma once

#include <glew.h>
#include "..\math\maths.h"

namespace seng
{
	namespace graphics
	{
		class Shader
		{
		private:
			GLuint m_shaderID;
			const char *m_vertPath, *m_fragPath;

		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();

			void setUniform1f(const GLchar *name, const float value);
			void setUniform1i(const GLchar *name, const int value);
			void setUniform2f(const GLchar *name, const math::Vector2f &vector);
			void setUniform3f(const GLchar *name, const math::Vector3f &vector);
			void setUniform4f(const GLchar *name, const math::Vector4f &vector);
			void setUniformMat4f(const GLchar *name, const math::Matrix4f &matrix);
			
			void enable() const;
			void disable() const;

		private:
			GLuint load();
			GLint getUniformLocation(const GLchar* name);
		};
	}
}