#pragma once
namespace Valar
{
	class FpsLimiter
	{
	public:
		FpsLimiter();
		void Init(float targetFPS);
		void SetTargetFPS(float targetFPS);
		void Begin();
		float End();
		void CalculateFPS();
	private:
		float _targetFps;
		unsigned int _startTicks;
		float _frameTime;
		float _fps;
		float _maxFPS;
	};

}