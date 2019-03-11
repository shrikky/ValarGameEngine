#include "Player.h"
#include <SDL.h>


Player::Player()
{
	
}


Player::~Player()
{
}

void Player::init(int speed, glm::vec2 position, Valar::InputManager* inputManager)
{
	_speed = speed;
	_position = position;
	_color = Valar::Color(0, 0, 185, 255);
	_inputManager = inputManager;
}

void Player::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies)
{
	if(_inputManager->isKeyPressed(SDLK_w))
	{
		_position.y += _speed;
	}
	else if (_inputManager->isKeyPressed(SDLK_s))
	{
		_position.y -= _speed;
	}
	if (_inputManager->isKeyPressed(SDLK_d))
	{
		_position.x += _speed;
	}
	else if (_inputManager->isKeyPressed(SDLK_a))
	{
		_position.x -= _speed;
	}

	collideWithLevel((levelData));
}
