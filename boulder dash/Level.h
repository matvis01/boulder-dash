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
	GameTile * tiles[mapSizeX][mapSizeY];


	Level();
	~Level();

	void removeTile(int x, int y);
	void setupLevel();
	void render(RenderTarget* target);

};

