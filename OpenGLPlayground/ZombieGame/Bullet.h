#pragma once
#include <detail/type_vec2.hpp>

class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 direction, float speed, int lifeTime);
	~Bullet();

private:
	float _damage;
	glm::vec2 _position;
	glm::vec2 _direction;
	float _speed;


};

