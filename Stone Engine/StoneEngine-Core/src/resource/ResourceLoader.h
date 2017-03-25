#pragma once

#include <string>
#include <FreeImage.h>
#include <glew.h>
#include <iostream>

namespace seng
{
	namespace resource 
	{
		struct ResourceLoader //TODO: move all I/O actions here, including loadShader or loadObject, etc.
		{
			static std::string readFile(const char* filepath);
			static BYTE* loadImage(const char* filepath, GLsizei* width, GLsizei* height);
		};
	}
}