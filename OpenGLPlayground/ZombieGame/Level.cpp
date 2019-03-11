#include "Level.h"
#include <fstream>
#include <Valar/Errors.h>
#include <Valar/ResourceManager.h>

Level::Level(const std::string& fileName)
{
	Valar::Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;
	std::ifstream file;
	file.open(fileName);
	if (file.fail())
	{
		Valar::fatalError("Failed To Open the File " + fileName);
		return;
	}
	std::string tmp;
	file >> tmp >> _numHumans;
	std::getline(file, tmp); // Throw away first line

	while (std::getline(file, tmp))
	{
		_levelData.push_back(tmp);
	}
	_spriteBatch.Init();
	_spriteBatch.Begin();

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	for (int x = 0; x < _levelData.size(); x++)
	{
		for (int y = 0; y < _levelData[x].size(); y++)
		{
			char tile = _levelData[x][y];
			glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_HEIGHT);
			switch (tile)
			{
			case 'R':
				{
					unsigned int red = Valar::ResourceManager::GetTexture("Textures/red_bricks.png").id;
					_spriteBatch.Draw(destRect, uvRect, red, 0, whiteColor);
				}
				break;
			case 'G':
				{
					unsigned int glass = Valar::ResourceManager::GetTexture("Textures/glass.png").id;
					_spriteBatch.Draw(destRect, uvRect, glass, 0, whiteColor);
				}
				break;
			case 'B':
				break;
			case 'Z':
			{		_levelData[x][y] = '.';
					_zombieStartPos.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
			}
			break;
			case '@':
				{
					_levelData[x][y] = '.';
					_startPlayerPos.x = x * TILE_WIDTH;
					_startPlayerPos.y = y * TILE_WIDTH;
				}
				break;
			case 'L':
				{
					unsigned int lightBricks = Valar::ResourceManager::GetTexture("Textures/light_bricks.png").id;
					_spriteBatch.Draw(destRect, uvRect, lightBricks, 0, whiteColor);
				}
				break;
			case '.' :
					break;
			default:
				std::printf("Unexpected symbol %c at (%d,%d)", tile, x, y);
				break;
			}
		}
	}
	_spriteBatch.End();
}


Level::~Level()
{
}

void Level::Draw()
{
	_spriteBatch.RenderBatch();
}

void Level::LoadLevel()
{
}
