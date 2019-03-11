#pragma once
#include <map>
#include "GLTexture.h"
namespace Valar
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();
		GLTexture GetTexture(std::string path);

	private:
		std::map<std::string, GLTexture> _textureMap;

	};

}