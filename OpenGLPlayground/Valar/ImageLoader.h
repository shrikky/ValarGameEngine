#pragma once
#include "GLTexture.h"
#include <string>
namespace Valar
{
	class ImageLoader
	{
	public:
		static GLTexture LoadPNG(std::string filePath);
	};

}

