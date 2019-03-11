#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
namespace Valar
{
	enum WindowFlags
	{
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};

	class Window
	{
	public:
		Window();
		~Window();
		int Create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
		int GetScreenWidth() { return _screenWidth; }
		int GetScreenHeight() { return _screenHeight; }
		void SwapBuffer();
	private:
		SDL_Window* _sdlWindow;
		int _screenWidth;
		int _screenHeight;
	};

}