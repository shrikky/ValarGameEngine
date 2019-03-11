#pragma once
#include <string>
#include "Bullet.h"
#include <detail/type_vec2.hpp>
#include <vector>
#include "Bullet.h"

class Gun
{

private:
	int _fireRate;
	int _bulletsPerShot;
	float _spread;
	float _bulletSpeed;
	int _bulletDamage;
	int _frameCounter;
	std::string _name;

public:
	Gun(std::string name, int fireRate, int bulletsPerShot, float spread, float bulletDamage, float bulletSpeed);
	~Gun();
	void update(bool isMouseDown, glm::vec2 direction, std::vector<Bullet>& bullets);
	void fire(glm::vec2 direction, std::vector<Bullet>&bullets);
};

