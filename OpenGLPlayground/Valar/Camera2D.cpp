#include "Camera2D.h"
#include <glm/glm.hpp>

namespace Valar {
	Camera2D::Camera2D()
	{
		_cameraMatrix = glm::mat4(1.0f);
		_orthoMatrix = glm::mat4(1.0f);
		_scale= 1.0f;
		_drityMatrix = true;
		_screenWidth = 500;
		_screenHeight = 500;
		_position = glm::vec2(0, 0);
	}


	Camera2D::~Camera2D()
	{

	}

	void Camera2D::Init(int screenWidth, int screenHeight)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);
	}

	void Camera2D::Update()
	{
		if (_drityMatrix)
		{
			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			glm::vec3 scale(_scale, _scale, 0.0f);
			_cameraMatrix = glm::scale(glm::mat4(1.0f),scale)*_cameraMatrix;

			_drityMatrix = false;
		}
	}
	glm::vec2 Camera2D::ScreenToWorld(glm::vec2 screenCoord)
	{
		screenCoord -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		screenCoord /= _scale;
		screenCoord += _position;
		return screenCoord;
	}
}