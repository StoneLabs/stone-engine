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

		BYTE* ResourceLoader::loadImage(const char* filepath, GLsizei* width, GLsizei* height)
		{
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			FREE_IMAGE_FORMAT fifFE = FIF_UNKNOWN;
			FREE_IMAGE_FORMAT fifFC = FIF_UNKNOWN;
			FIBITMAP *dib = nullptr;
			fifFC = FreeImage_GetFileType(filepath, 0);
			fifFE = FreeImage_GetFIFFromFilename(filepath);
			if (fifFC == FIF_UNKNOWN && fifFE != FIF_UNKNOWN)
			{
				std::cout << "Warning: Could not detect image format, assuming file extension is correct for " << filepath << std::endl;
				fif = fifFE;
			}
			else if (fifFC != fifFE)
				std::cout << "Warning: Image format and extension do not match for " << filepath << std::endl;
			else
				fif = fifFC;
			if (fif == FIF_UNKNOWN)
			{
				std::cout << "Error: Could not read image (UNKNOWN TYPE): " << filepath << std::endl;
				return nullptr;
			}

			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, filepath);
			if (!dib)
			{
				std::cout << "Error: Could not read image (LOAD ERROR): " << filepath << std::endl;
				return nullptr;
			}

			BYTE* result	= FreeImage_GetBits(dib);
			*width			= FreeImage_GetWidth(dib);
			*height			= FreeImage_GetHeight(dib);
			
			return result;
		}
	}
}