#include "Window.h"
#include "Errors.h"

namespace Valar
{
	Window::Window()
	{
	}


	Window::~Window()
	{
	}

	int Window::Create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{

		Uint32 flags = SDL_WINDOW_OPENGL;
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;

		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN) {
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}

		//Open an SDL window
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

		if (_sdlWindow == nullptr)
		{
			fatalError("SDL window could not be created!");
			return 0;
		}
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext = nullptr)
		{
			fatalError("SDL_GL context cannot be created!");
			return 0;
		}
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			fatalError("Glew not initialized!");
			return 0;
		}
		printf("*** OpenGL Version: %s ****", glGetString(GL_VERSION));
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);


		//Enable Blend
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		SDL_GL_SetSwapInterval(0);
		return 1;
	}

	void Window::SwapBuffer()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}
}