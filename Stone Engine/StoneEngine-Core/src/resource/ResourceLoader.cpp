#include <string>
#include "ResourceLoader.h"

namespace seng
{
	namespace resource
	{
		std::string ResourceLoader::readFile(const char* filepath)
		{
			FILE* file = fopen(filepath, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long long length = ftell(file);

			char* data = new char[length + 1];
			memset(data, 0, length + 1);

			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}
	}
}