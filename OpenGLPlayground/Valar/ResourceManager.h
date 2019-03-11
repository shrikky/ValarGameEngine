#pragma once
#include "TextureCache.h"
namespace Valar
{
	class ResourceManager
	{
	public:
		static GLTexture GetTexture(std::string texturepath);


	private:
		static TextureCache _texturecache;

	};

}