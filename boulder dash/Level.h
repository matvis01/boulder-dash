#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <regex>
#include <sstream>
#include <fstream>
#include "functions.h"
#include "Player.h"
#include "GameTile.h"
#include <vector>
#include "Wall.h"
#include "Ground.h"
#include "Rock.h"
#include "Diamond.h"
#include "EndLvl.h"


namespace fs = std::filesystem;
using namespace std;

class Level
{

public:
	int mapSizeX = 0;
	int mapSizeY = 0;
	tilePos playerStartingPos;

	fs::path levelsPath = "./levels/";
	vector<fs::path> allPaths;

	vector<std::vector<std::shared_ptr<GameTile>>> tiles;
	vector <std::shared_ptr<GameTile>> allFallable;

	int diamondsRequired = 1;
	int diamondsCollected = 0;

	int currentLevel = 0;
	int howManyLevels = 0;

	Level();
	~Level();

	void setupLevel();
	void render(RenderTarget* target);

	void clearLevel();
};

