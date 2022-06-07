#pragma once

#include <iostream>
#include "functions.h"

using namespace sf;


class Player
{
	float movementSpeed;
	float nextSpot;
	int sizeX;
	int sizeY;
	Vector2f playerPos;

	Texture texture;
	Sprite sprite;
	IntRect source;

	void initVeriables();
	void setUpSprite();
	void movement();

	Clock animationClock;
	Clock standingClock;
	Thread thr{ &Player::waitToStand,this };
	SoundBuffer buffer1, buffer2;
	

public:
	bool isMoving;
	bool direction[4];
	bool movedLeft;
	float squareSize;
	Sound hitSound, dirtSound;

	tilePos playerPosTile;
	Vector2f getPlayerPos();
	float getPlayerSpeed();
	Player();
	~Player();

	void waitToStand();
	void playHitSound();
	void setPlayerPos(tilePos);
	void updateInput(bool, bool, bool, bool);
	void update(bool, bool, bool, bool);
	void render(RenderTarget* target);

};

