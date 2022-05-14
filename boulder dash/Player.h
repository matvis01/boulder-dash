#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
//#include "GameTile.h"
#include "functions.h"

using namespace sf;


class Player
{
	float movementSpeed;


	float nextSpot;
	
	Vector2f playerPos;


	Texture texture;
	Sprite sprite;
	
	void initVeriables();
	void setSize();
	void movement();


public:
	bool isMoving;
	bool direction[4];
	bool movedLeft;
	float squareSize;

	tilePos playerPosTile;
	Vector2f getPlayerPos();
	float getPlayerSpeed();
	Player();
	~Player();

	void setPlayerPos(tilePos);
	void updateInput(bool, bool, bool, bool);
	void update(bool, bool, bool, bool);
	void render(RenderTarget* target);

};

