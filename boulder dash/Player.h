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
	bool direction[4];
	Vector2f playerPos;


	Texture texture;
	Sprite sprite;
	
	void initVeriables();
	void setSize();
	void movement();


public:
	float squareSize;

	tilePos playerPosTile;
	Vector2f getPlayerPos();
	Player();
	~Player();

	void updateInput(bool, bool, bool, bool);
	void update(bool, bool, bool, bool);
	void render(RenderTarget* target);

};

