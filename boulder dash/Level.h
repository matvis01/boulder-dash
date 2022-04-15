#pragma once
#include <iostream>
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

class Level
{
	Vector2f playerPos;
public:
	const static int mapSizeX = 30;
	const static int mapSizeY = 23;
	std::shared_ptr<GameTile> tiles[mapSizeX][mapSizeY];
	std::vector <std::shared_ptr<GameTile>> allFallable;


	Level();
	~Level();

	void setupLevel();
	void render(RenderTarget* target);

};

