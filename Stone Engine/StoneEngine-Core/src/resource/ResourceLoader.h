#pragma once

#include <string>

namespace seng
{
	namespace resource 
	{
		struct ResourceLoader //TODO: move all I/O actions here, including loadShader or loadObject, etc.
		{
			static std::string readFile(const char* filepath);
		};
	}
}