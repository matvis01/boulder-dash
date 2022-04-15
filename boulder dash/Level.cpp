#include "Level.h"

Level::Level()
{
	setupLevel();
}

Level::~Level()
{

}



void Level::setupLevel()
{
	for (int i = 0; i < this->mapSizeX; i++)
	{
		for (int j = 0; j < this->mapSizeY; j++)
		{
			tiles[i][j] = nullptr;
		}
	}

	int x = 1, y = 0;
	tiles[x][y] = std::make_shared<Wall>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 2; y = 0;
	tiles[x][y] = std::make_shared<Wall>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 3; y = 0;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 4; y = 0;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 5; y = 0;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 0;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 4;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 5; y = 6;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 4;
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 3;										
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 6;										
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 7;										  
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 3;										
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 6;										
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 7;										 
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 8;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 7;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 6;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 8; y = 7;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 8; y = 6;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);

	for (int i = 0; i < this->mapSizeX; i++)
	{
		for (int j = 0; j < this->mapSizeY; j++)
		{
			if (tiles[i][j] != nullptr and tiles[i][j]->getName() == Name::rock)
			{
				this->allFallable.push_back(tiles[i][j]);
				tiles[i][j]->tilePosition.x = i;
				tiles[i][j]->tilePosition.y = j;
			}
		}
	}
}

void Level::render(RenderTarget* target)
{
	for (int i = 0; i < mapSizeY; i++)
	{
		for (int j = 0; j < mapSizeX; j++)
		{
			if (tiles[j][i] != nullptr)
			{
				tiles[j][i]->render(target);
			}
		}
	}
}
