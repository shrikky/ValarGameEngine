#include "Zombie.h"
#include "Valar/ResourceManager.h"

Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 pos)
{
	_speed = speed;
	_position = pos;
	// Set Green Color
	_color = Valar::Color(255, 255, 255, 255);
	//m_textureID = Valar::ResourceManager::GetTexture("Textures/zombie.png").id;
}

void Zombie::update(const std::vector<std::string>& levelData, std::vector<Human*>& humans, std::vector<Zombie*>& zombies)
{
	Human* nearestHuman = getNearestHuman();
	if(nearestHuman !=nullptr)
	{
		glm::vec2 direction = glm::normalize(nearestHuman->getPosition() - _position);
		_position += direction * _speed;
	}
}

Human * Zombie::getNearestHuman(std::vector<Human*>& humans)
{
	Human* closestHuman = nullptr;
	float smallestDistance = 9999999.0f;

	for (int i = 0; i < humans.size(); i++) {
		// Get the direction vector
		glm::vec2 distVec = humans[i]->getPosition() - _position;
		// Get distance
		float distance = glm::length(distVec);

		// If this person is closer than the closest person, this is the new closest
		if (distance < smallestDistance) {
			smallestDistance = distance;
			closestHuman = humans[i];
		}
	}

	return closestHuman;
}

