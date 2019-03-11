#pragma once
#include <Valar\Window.h>
#include <Valar\GLSLProgram.h>
#include <Valar\Camera2D.h>
#include <Valar\InputManager.h>
#include "Level.h"
#include "Human.h"
#include "Zombie.h"
#include "Player.h"

enum class GameState
{
	PLAY, EXIT
};
class MainGame
{

public:
	MainGame();
	~MainGame();

	const float HUMAN_SPEED = 1.0f;
	const float PLAYER_SPEED = 10.0f;
	const float ZOMBIE_SPEED = 1.3f;
	/// Runs the game
	void run();

private:
	/// Initializes the core systems
	void initSystems();

	void initLevel();
	/// Initializes the shaders
	void initShaders();

	void updateAgents();
	/// Main game loop for the program
	void gameLoop();
	/// Handles input processing
	void processInput();
	/// Renders the game
	void drawGame();

private:
	/// Member Variables
	Valar::Window _window; ///< The game window
	Valar::GLSLProgram _textureProgram; ///< The shader program
	Valar::InputManager _inputManager; ///< Handles input
	Valar::Camera2D _camera; ///< Main Camera
	std::vector <Level*> _levels;
	GameState _gameState;
	int _currentLevel;
	float _fps;
	std::vector<Human*> _humans;
	std::vector<Zombie*> _zombies;
	Player* _player;
	Valar::SpriteBatch _agentSpriteBatch;
};

