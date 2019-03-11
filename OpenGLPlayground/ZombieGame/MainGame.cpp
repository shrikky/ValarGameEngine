#include "MainGame.h"
#include <SDL/SDL.h>
#include <iostream>
#include <Valar/Valar.h>
#include "Player.h"
#include <Valar/Timing.h>
#include <random>
#include <ctime>
#include "Valar/Errors.h"

MainGame::MainGame() 
{
	_gameState = GameState::PLAY;
	_fps = 0;
	_player = nullptr;
}

MainGame::~MainGame()
{
	for (int i = 0; i < _levels.size(); i++)
	{
		delete(_levels[i]);
	}
	// Empty
}

void MainGame::run() {

	initSystems();
	initLevel();
	gameLoop();
}

void MainGame::initSystems() {
	Valar::Init();

	_window.Create("Zombie Game", 1024, 800, 0);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	initShaders(); 
	_agentSpriteBatch.Init();
	_camera.Init(1024, 800);
}

void MainGame::initShaders() {
	// Compile our color shader
	_textureProgram.CompileShaders("Shaders/VertexShader.vs", "Shaders/FragmentShader.fs");
	_textureProgram.AddAttribute("vertexPosition");
	_textureProgram.AddAttribute("vertexColor");
	_textureProgram.AddAttribute("vertexUV");
	_textureProgram.LinkShaders();
}
void MainGame::initLevel()
{
	_currentLevel = 0;
	_levels.push_back(new Level("Levels/level1.txt"));
	_player = new Player;
	_player->init(PLAYER_SPEED, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager);

	_humans.push_back(_player);

	static std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));

	static std::uniform_int_distribution<int> randX(1, _levels[_currentLevel]->getWidth() - 2);
	static std::uniform_int_distribution<int> randY(1, _levels[_currentLevel]->getHeight() - 2);

	for(int i =0 ; i<_levels[_currentLevel]->getNumHumans();i++)
	{
		_humans.push_back((new Human));
		glm::vec2 pos(randX(randomEngine)* TILE_WIDTH, randY(randomEngine)* TILE_WIDTH);
		_humans.back()->init(HUMAN_SPEED, pos);
	
	}

	const std::vector<glm::vec2>& zombiePositions = _levels[_currentLevel]->getZombiesStartpos();
	for(int i =0;i<zombiePositions.size();i++)
	{
		_zombies.push_back(new Zombie);
		_zombies.back()->init(ZOMBIE_SPEED, zombiePositions[i]);
	}
}

void MainGame::gameLoop() 
{
	Valar::FpsLimiter fpsLimiter;
	fpsLimiter.SetTargetFPS(60);
	while(_gameState == GameState::PLAY)
	{
		fpsLimiter.Begin();
		processInput();
		_camera.SetPosition(_player->getPosition());
		_camera.Update();
		updateAgents();
		drawGame();
		_fps = fpsLimiter.End();
	}
}

void MainGame::processInput() {
	SDL_Event evnt;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			//Exit the game here!
			break;
		case SDL_MOUSEMOTION:
			_inputManager.SetMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.PressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.ReleaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.PressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.ReleaseKey(evnt.button.button);
			break;
		}

	}

}
void MainGame::updateAgents()
{
	// Update all humans
	for (int i = 0; i < _humans.size(); i++) {
		_humans[i]->update(_levels[_currentLevel]->getLevelData(),
			_humans,
			_zombies
			);
	}

	// Update all zombies
	for (int i = 0; i < _zombies.size(); i++) {
		_zombies[i]->update(_levels[_currentLevel]->getLevelData(),
			_humans,
			_zombies);
	}

	// Update Zombie collisions
	for (int i = 0; i < _zombies.size(); i++) {
		// Collide with other zombies
		for (int j = i + 1; j < _zombies.size(); j++) {
			_zombies[i]->collideWithAgent(_zombies[j]);
		}
		// Collide with humans
		for (int j = 1; j < _humans.size(); j++) {
			if (_zombies[i]->collideWithAgent(_humans[j])) {
				// Add the new zombie
				_zombies.push_back(new Zombie);
				_zombies.back()->init(ZOMBIE_SPEED, _humans[j]->getPosition());
				// Delete the human
				delete _humans[j];
				_humans[j] = _humans.back();
				_humans.pop_back();
			}
		}

		// Collide with player
		if (_zombies[i]->collideWithAgent(_player)) {
			Valar::fatalError("YOU LOSE");
		}
	}

	// Update Human collisions
	for (int i = 0; i < _humans.size(); i++) {
		// Collide with other humans
		for (int j = i + 1; j < _humans.size(); j++) {
			_humans[i]->collideWithAgent(_humans[j]);
		}
	}

}
void MainGame::drawGame() {
	// Set the base depth to 1.0
	glClearDepth(1.0);
	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_textureProgram.Use();
	//Draw code goes here
	glActiveTexture(GL_TEXTURE0);

	// Make sure the shader uses Texture unit location 0
	GLint textureUniform = _textureProgram.GetUnitformLocation("playerTexture");
	glUniform1i(textureUniform, 0);

	glm::mat4 projectionMatrix = _camera.GetCameraMatrix();
	GLint pUniform = _textureProgram.GetUnitformLocation("proj");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);
	//Swap our buffer and draw everything to the screen!

	//Draw Level
	_levels[_currentLevel]->Draw();
	//Draw Humans
	_agentSpriteBatch.Begin();
	for(int i =0; i<_humans.size(); i++)
	{
		_humans[i]->draw(_agentSpriteBatch);
	}

	for (int i = 0; i < _zombies.size(); i++)
	{
		_zombies[i]->draw(_agentSpriteBatch);
	}
	_agentSpriteBatch.End();
	_agentSpriteBatch.RenderBatch();
	_textureProgram.Unuse();
	_window.SwapBuffer();
}