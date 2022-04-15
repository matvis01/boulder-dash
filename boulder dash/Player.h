#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
//#include "GameTile.h"


using namespace sf;

enum MoveDirection { UP, DOWN, LEFT, RIGHT };

struct tilePos
{
	int x;
	int y;
};

class Player
{
	float movementSpeed;

	bool isMoving;
	float nextSpot;
	
	Vector2f playerPos;


	Texture texture;
	Sprite sprite;
	
	void initVeriables();
	void setSize();
	void movement();


public:
	bool direction[4];
	bool movedLeft;
	float squareSize;

	tilePos playerPosTile;
	Vector2f getPlayerPos();
	float getPlayerSpeed();
	Player();
	~Player();

	void updateInput(bool, bool, bool, bool);
	void update(bool, bool, bool, bool);
	void render(RenderTarget* target);

};

