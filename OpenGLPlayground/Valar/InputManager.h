#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
namespace Valar {
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void PressKey(unsigned int keyID);
		void ReleaseKey(unsigned int keyID);
		bool isKeyPressed(unsigned int keyID);
		void SetMouseCoords(int x, int y);

		glm::vec2 GetMouseCoords() const 
		{
			return _mouseCoords;
		}

	private:
		std::unordered_map<unsigned int, bool> _keyMap;
		glm::vec2 _mouseCoords;
	};

}