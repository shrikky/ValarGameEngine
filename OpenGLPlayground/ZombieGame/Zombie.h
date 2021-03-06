#pragma once
#include "Agent.h"
#include "Human.h"

class Zombie : public Agent
{
public:
	Zombie();
	~Zombie();

	void init(float speed, glm::vec2 pos);
	 void update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies) override;
	 Human* getNearestHuman(std::vector<Human*>& humans);
};

