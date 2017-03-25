#include "Shader.h"

namespace seng
{
	namespace graphics
	{
		Shader::Shader(const char* vertPath, const char* fragPath) :
			m_vertPath(vertPath), m_fragPath(fragPath)
		{
			m_shaderID = load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_shaderID);
		}

		GLuint Shader::load()
		{
			using namespace seng::resource;

			GLuint program	= glCreateProgram();
			GLuint vertex	= glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment	= glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertexCode = ResourceLoader::readFile(m_vertPath);
			std::string fragmentCode = ResourceLoader::readFile(m_fragPath);

			const char *vertSource = vertexCode.c_str();
			const char *fragSource = fragmentCode.c_str();
			
			glShaderSource(vertex, 1, &vertSource, NULL);
			glCompileShader(vertex);

			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Failed to compile vertex shader!" << std::endl;
				std::cout << &error[0] << std::endl;

				glDeleteShader(vertex);
				return 0;
			}

			glShaderSource(fragment, 1, &fragSource, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to compile fragment shader!" << std::endl;
				std::cout << &error[0] << std::endl;

				glDeleteShader(fragment);
				return 0;
			}
			
			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		void Shader::enable() const { glUseProgram(m_shaderID); }
		void Shader::disable() const { glUseProgram(0); }

#pragma region Uniforms
		GLint Shader::getUniformLocation(const GLchar *name)
		{
			return glGetUniformLocation(m_shaderID, name);
		}

		void Shader::setUniform1f(const GLchar *name, const float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform1i(const GLchar *name, const int value)
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniform2f(const GLchar *name, const math::Vector2f &vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniform3f(const GLchar *name, const math::Vector3f &vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniform4f(const GLchar *name, const math::Vector4f &vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniformMat4f(const GLchar *name, const math::Matrix4f &matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}
#pragma endregion
	}
}