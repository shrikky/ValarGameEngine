#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Valar.h"
namespace Valar
{
	int Init()
	{
		//Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		return 1;
	}
}
