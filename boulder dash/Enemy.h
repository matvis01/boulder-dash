#pragma once
#include <iostream>
#include "functions.h"

using namespace sf;

class Enemy
{
	float movementSpeed;
	float nextSpot;
	int sizeX;
	int sizeY;
	int lastDir;
	Vector2f Pos;

	Texture texture;
	Sprite sprite;
	IntRect source;

	void initVeriables();
	void setUpSprite();
	void movement();

	Clock animationClock;

public:
	bool isMoving;
	bool direction[4];
	//bool canGoDir[4];
	float squareSize;
	tilePos PosTile;

	Enemy(tilePos);
	~Enemy();

	void updateMovement(bool[4]);
	void update(bool[4]);
	void render(RenderTarget* target);
};

