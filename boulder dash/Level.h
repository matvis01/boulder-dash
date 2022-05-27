#pragma once
#include <iostream>
#include <filesystem>
#include<string>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"
#include "GameTile.h"
#include <vector>
#include "Wall.h"
#include "Ground.h"
#include "Rock.h"
#include "Diamond.h"
#include "EndLvl.h"
#include "functions.h"

namespace fs = std::filesystem;

class Level
{

public:
	int mapSizeX;
	int mapSizeY;
	tilePos playerStartingPos;

	std::vector<std::vector<std::shared_ptr<GameTile>>> tiles;
	std::vector <std::shared_ptr<GameTile>> allFallable;

	int diamondsRequired = 1;
	int diamondsCollected = 0;

	int currentLevel = 1;
	int howManyLevels = 2;

	Level();
	~Level();

	void setupLevel();
	void level2();
	void render(RenderTarget* target);

	void clearLevel();
	void chooseLevel();
};

