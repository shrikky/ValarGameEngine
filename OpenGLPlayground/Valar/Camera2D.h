#pragma once
#include <glm/gtc/matrix_transform.hpp>
namespace Valar {
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void Init(int screenWidth, int screenHeight);
		void SetPosition(glm::vec2 newPosition )
		{
			_position = newPosition;
			_drityMatrix = true;
		}
		void SetScale(float newScale)
		{
			_scale = newScale;
			_drityMatrix = true;
		}


		void  Update();

		glm::vec2 ScreenToWorld(glm::vec2 screenCoord);
		//getters
		glm::vec2& GetPosition() { return _position; }
		float GetScale() { return _scale; }
		glm::mat4& GetCameraMatrix() { return _cameraMatrix; }
		float GetAspectRatio() { return (float)_screenWidth / (float)_screenHeight; }

	private:

		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		bool _drityMatrix;
		int _screenWidth, _screenHeight;
		glm::mat4 _orthoMatrix;

	};

}