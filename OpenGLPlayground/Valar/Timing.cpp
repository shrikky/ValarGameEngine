#include "Timing.h"
#include <SDL/SDL.h>

namespace Valar
{
	FpsLimiter::FpsLimiter() 
	{

	}
	void FpsLimiter::Init(float targetFPS)
	{
		SetTargetFPS(targetFPS);
	}
	void FpsLimiter::SetTargetFPS(float targetFPS)
	{
		_maxFPS = targetFPS;
	}
	void FpsLimiter::Begin() {
		_startTicks = SDL_GetTicks();
	}
	float FpsLimiter::End()
	{
		CalculateFPS();
		float frameTicks = SDL_GetTicks() - _startTicks;
		if (1000.0f / _maxFPS > frameTicks)
		{
			SDL_Delay(1000.0f / _maxFPS - frameTicks);
		}
		return _fps;
	}

	void FpsLimiter::CalculateFPS()
	{
		static const int NUM_SAMPLES = 100;
		static float frameTimes[NUM_SAMPLES];
		static float prevTicks = SDL_GetTicks();
		static int currentFrame = 0;
		float currentTicks;


		currentTicks = SDL_GetTicks();
		_frameTime = currentTicks - prevTicks;

		// Sets the value in array of 10 
		frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

		prevTicks = currentTicks;
		currentFrame++;
		int count;
		if (currentFrame < NUM_SAMPLES)
		{
			count = currentFrame;
		}
		else
		{
			count = NUM_SAMPLES;
		}


		float frameTimeAverage = 0;
		for (int i = 0; i < count; i++)
		{
			frameTimeAverage += frameTimes[i];
		}
		frameTimeAverage /= count;

		if (frameTimeAverage > 0)
		{
			_fps = 1000.0f / frameTimeAverage;
		}
		else
		{
			_fps = 60.0f;
		}

	}
}