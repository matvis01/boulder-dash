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
	this->playerStartingPos = { 0,0 };

	mapSizeX = 30;
	mapSizeY = 25;

	diamondsCollected = 0;
	diamondsRequired = 1;

	for (int i = 0; i < this->mapSizeX; i++)
	{
		std::vector <std::shared_ptr<GameTile>> temp;

		for (int j = 0; j < this->mapSizeY; j++)
		{
			temp.push_back(nullptr);
		}
		tiles.push_back(temp);
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
	x = 7; y = 0;
	tiles[x][y] = std::make_shared<Diamond>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 8; y = 0;
	tiles[x][y] = std::make_shared<EndLvl>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 3; y = 1;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 4;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 5;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 5; y = 6;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 3;										
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 3;										
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 6;										
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 7;										 
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 7;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 8;
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
			if (tiles[i][j] != nullptr and tiles[i][j]->movable)
			{
				this->allFallable.push_back(tiles[i][j]);
				tiles[i][j]->tilePosition.x = i;
				tiles[i][j]->tilePosition.y = j;
			}
		}
	}

}

void Level::level2()
{
	this->playerStartingPos = { 1,0 };

	mapSizeX = 30;
	mapSizeY = 25;

	diamondsCollected = 0;
	diamondsRequired = 1;

	for (int i = 0; i < this->mapSizeX; i++)
	{
		std::vector <std::shared_ptr<GameTile>> temp;

		for (int j = 0; j < this->mapSizeY; j++)
		{
			temp.push_back(nullptr);
		}
		tiles.push_back(temp);
	}

	int x = 6, y = 0;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 0;
	tiles[x][y] = std::make_shared<Diamond>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 4;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 5; y = 6;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 3;
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 3;
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 6;
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 7;
	tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 7;
	tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 8;
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
			if (tiles[i][j] != nullptr and tiles[i][j]->movable)
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

void Level::clearLevel()
{
	allFallable.clear();

	for (int i = 0; i < tiles.size()-1; i++)
	{
		tiles[i].clear();
	}
	tiles.clear();
}

void Level::chooseLevel()
{
	if (currentLevel == 1)
		setupLevel();  // change to lvl 1
	if (currentLevel == 2)
		level2();
}
