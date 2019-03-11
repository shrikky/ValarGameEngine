#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <Valar/Valar.h>
#include <Valar/GLSLProgram.h>
#include <Valar/Window.h>
#include <vector>
#include <Valar/SpriteBatch.h>
#include <Valar/Camera2D.h>
#include <Valar/InputManager.h>
#include <Valar/Timing.h>
#include "Bullet.h"
enum class GameState {PLAY, EXIT};
class MainGame
{
public:
	MainGame();
	~MainGame();

	void Run();
	void InitSystems();
	void GameLoop();
	void ProcessInput();
	void DrawGame();
	void InitShaders();

private:
	int _screenWidth;
	int _screenHeight;
	GameState _currentGameState;
	float _time;
	float _frameTime;
	float _fps;
	float _maxFPS;
	Valar::GLSLProgram _colorProgram;
	Valar::Window _window;
	Valar::Camera2D _camera;
	Valar::SpriteBatch _spriteBatch;
	Valar::InputManager _inputManager;
	Valar::FpsLimiter _fpsLimiter;
	std::vector<Bullet> _bullets;
};

