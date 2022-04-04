#include "Level.h"

Level::Level()
{
	setupLevel();
}

Level::~Level()
{

}


void Level::removeTile(int x, int y)
{
	delete tiles[x][y];
}

void Level::setupLevel()
{
	int x = 1, y = 0;
	tiles[x][y] = new Wall(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 2; y = 0;
	tiles[x][y] = new Wall(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 3; y = 0;
	tiles[x][y] = new Ground(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 4; y = 0;
	tiles[x][y] = new Ground(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 5; y = 0;
	tiles[x][y] = new Ground(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 0;
	tiles[x][y] = new Rock(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 4;
	tiles[x][y] = new Ground(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 5; y = 6;
	tiles[x][y] = new Ground(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 4;
	tiles[x][y] = new Rock(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 3;
	tiles[x][y] = new Rock(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 6;
	tiles[x][y] = new Rock(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 7;
	tiles[x][y] = new Rock(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 3;
	tiles[x][y] = new Rock(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 6;
	tiles[x][y] = new Rock(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 7;
	tiles[x][y] = new Rock(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 7; y = 8;
	tiles[x][y] = new Ground(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 7;
	tiles[x][y] = new Ground(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 6; y = 6;
	tiles[x][y] = new Ground(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 8; y = 7;
	tiles[x][y] = new Ground(x * 80.f + 40.f, y * 80.f + 40.f);
	x = 8; y = 6;
	tiles[x][y] = new Ground(x * 80.f + 40.f, y * 80.f + 40.f);
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
