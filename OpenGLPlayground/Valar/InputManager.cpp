#include "InputManager.h"

namespace Valar {

	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::PressKey(unsigned int keyID)
	{

		_keyMap[keyID] = true;
	}

	void InputManager::ReleaseKey(unsigned int keyID)
	{
		_keyMap[keyID] = false;
	}

	bool InputManager::isKeyPressed(unsigned int keyID)
	{
		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end())
		{
			return it->second;
		}
		return false;
	}
	void InputManager:: SetMouseCoords(int x, int y)
	{
		_mouseCoords.x = x;
		_mouseCoords.y = y;
	}
}