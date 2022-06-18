#include "Level.h"

Level::Level()
{
	if (exists(levelsPath))
	{
		for (const auto& entry : fs::directory_iterator(levelsPath))
		{
			if (entry.exists())
			{
				allPaths.push_back(entry);
				
			}
		}
	}
	howManyLevels = allPaths.size();

	setupLevel();
}

Level::~Level()
{
}

void Level::setupLevel()
{
	diamondsCollected = 0;
	diamondsRequired = 0;

	ifstream inputfile(allPaths[this->currentLevel]);
	string line;

	getline(inputfile, line);
	istringstream(line) >> mapSizeX >> mapSizeY;

	std::vector <std::shared_ptr<GameTile>> temp;
	for (int i = 0; i < this->mapSizeY; i++)
	{
		temp.push_back(nullptr);
	}
	for (int j = 0; j < this->mapSizeX; j++)
	{
		tiles.push_back(temp);
	}

	int x = 0, y = 0;
	regex re("[|]");

	while (getline(inputfile, line))
	{
		x = 0;

		for (int i = 0; i < line.length(); i++)
		{
			std::string single = line.substr(i, 1);
			if (regex_match(single, re))
			{
				if (line[i + 1] == 'p')
				{
					this->playerStartingPos = { x,y };
				}
				else if (line[i + 1] == 'w')
				{
					tiles[x][y] = std::make_shared<Wall>(x * 80.f + 40.f, y * 80.f + 40.f);
				}
				else if (line[i + 1] == 'd')
				{
					tiles[x][y] = std::make_shared<Diamond>(x * 80.f + 40.f, y * 80.f + 40.f);
					diamondsRequired++;
				}
				else if (line[i + 1] == 'f')
				{
					tiles[x][y] = std::make_shared<EndLvl>(x * 80.f + 40.f, y * 80.f + 40.f);
				}
				else if (line[i + 1] == ' ')
				{
					tiles[x][y] = std::make_shared<Ground>(x * 80.f + 40.f, y * 80.f + 40.f);
				}
				else if (line[i + 1] == 'r')
				{
					tiles[x][y] = std::make_shared<Rock>(x * 80.f + 40.f, y * 80.f + 40.f);
				}
				else if (line[i + 1] == 'e')
				{
					tilePos pos = { x,y };
					enemies.push_back(std::make_shared<Enemy>(pos));
				}
				x++;
			}
			
		}
		y++;
	}

	diamondsRequired -= 2;

	/*mapSizeX = tiles[0].size();
	mapSizeY = tiles.size();*/

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



void Level::renderEnemies(RenderTarget* target)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->render(target);
		}
	}
}



bool Level::enemyCanGoUp(int i)
{
	if (tiles[enemies[i]->PosTile.x][enemies[i]->PosTile.y - 1] == nullptr)
	{
		return true;
	}
	else
	{
		if (tiles[enemies[i]->PosTile.x][enemies[i]->PosTile.y - 1]->getIsMoving())
		{
			return true;
		}
		else 
		return false;
	}
}

bool Level::enemyCanGoDown(int i)
{
	if (tiles[enemies[i]->PosTile.x][enemies[i]->PosTile.y + 1] == nullptr)
	{
		return true;
	}
	else
	{

		if (tiles[enemies[i]->PosTile.x][enemies[i]->PosTile.y + 1]->getIsMoving())
		{
			return true;
		}
		else
			return false;
	}
}

bool Level::enemyCanGoLeft(int i)
{
	if (tiles[enemies[i]->PosTile.x-1][enemies[i]->PosTile.y] == nullptr)
	{
		return true;
	}
	else
	{
		if (tiles[enemies[i]->PosTile.x-1][enemies[i]->PosTile.y]->getIsMoving())
		{
			return true;
		}
		else
			return false;
	}
}

bool Level::enemyCanGoRight(int i)
{
	if (tiles[enemies[i]->PosTile.x+1][enemies[i]->PosTile.y] == nullptr)
	{
		return true;
	}
	else
	{
		if (tiles[enemies[i]->PosTile.x+1][enemies[i]->PosTile.y]->getIsMoving())
		{
			return true;
		}
		else
			return false;
	}
}

void Level::clearLevel()
{
	allFallable.clear();
	enemies.clear();

	for (int i = 0; i < tiles.size()-1; i++)
	{
		tiles[i].clear();
	}
	tiles.clear();
}
