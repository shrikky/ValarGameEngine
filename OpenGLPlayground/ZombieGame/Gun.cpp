#include "Gun.h"



Gun::Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletDamage, float bulletSpeed)
{
	_name = name;
	_fireRate = fireRate;
	_bulletsPerShot = bulletsPerShot;
	_spread = spread;
	_bulletSpeed = bulletSpeed;
	_bulletDamage = bulletDamage;
	_frameCounter = 0;
}

Gun::~Gun()
{
}

void Gun::update(bool isMouseDown, glm::vec2 direction, std::vector<Bullet>& bullets)
{
	_frameCounter++;
	if(_frameCounter >= _fireRate)
	{
		
	}
}

void Gun::fire(glm::vec2 direction, std::vector<Bullet>& bullets)
{
	for(int i = 0; i< _bulletsPerShot;i++)
	{
		bullets.emplace()
	}
}


