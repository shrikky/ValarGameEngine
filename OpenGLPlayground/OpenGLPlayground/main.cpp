#include <iostream>
#include <SDL/SDL.h>
#include "Maingame.h"

int main(int argc, char** argv)
{
	MainGame maingame;
	maingame.Run();
	int a;
	std::cin >> a;
	return 0;
}