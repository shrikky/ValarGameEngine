#pragma once
#include "Human.h"
#include "Valar/InputManager.h"

class Player : public Human
{
public:
	Player();
	~Player();
	void init(int speed, glm::vec2 position, Valar::InputManager* inputmanager);
	void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) override;

private:
	Valar::InputManager* _inputManager;
};

