#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>
namespace Valar
{

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::GetTexture(std::string path)
	{
		auto it = _textureMap.find(path);
		if (it == _textureMap.end())
		{
			GLTexture newTexture = ImageLoader::LoadPNG(path);
			_textureMap.insert(make_pair(path, newTexture));
			return newTexture;
		}
		return it->second;
	}
}