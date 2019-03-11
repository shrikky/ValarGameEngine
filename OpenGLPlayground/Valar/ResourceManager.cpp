#include "ResourceManager.h"
namespace Valar
{
	TextureCache ResourceManager::_texturecache;

	GLTexture ResourceManager::GetTexture(std::string texturepath)
	{
		return _texturecache.GetTexture(texturepath);
	}
}