#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"

using namespace sf;

enum class Name { rock, wall, ground };


class GameTile
{
protected:
	Name name;
	Texture texture;
	Sprite sprite;
	Vector2f position;

	std::string textureFile;
	const float tileSize = 80.f;
	float nextSpot = 0.f;
	float nextSpotSide = 0.f;


	void SetupSprite();
public:
	tilePos tilePosition;
	bool isPassable = 0;
	bool isMoving = 0;
	virtual bool getIsMoving() = 0;
	virtual void changeIsMoving() = 0;
	virtual bool fallDown() = 0;
	virtual bool fallLeft() = 0;
	virtual bool fallRight() = 0;
	virtual bool moveSideways(bool movesLeft, float speed) = 0;

	Name getName();
	Vector2f getPos();
	float getTileSize();
	void render(RenderTarget* target);
};

