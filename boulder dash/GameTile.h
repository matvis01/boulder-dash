#pragma once

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

using namespace sf;

class GameTile
{
protected:
	std::string name;
	Texture texture;
	Sprite sprite;
	Vector2f position;
	//tilePos tilePosition;
	std::string textureFile;
	const float tileSize = 80.f;
	float nextSpot;
	float nextSpotSide;


	void SetupSprite();
public:
	bool isPassable;
	bool isMoving;
	virtual bool getIsMoving() = 0;
	virtual void changeIsMoving() = 0;
	virtual bool fallDown() = 0;
	virtual bool fallLeft() = 0;
	virtual bool fallRight() = 0;

	std::string getName();
	Vector2f getPos();
	float getTileSize();
	void render(RenderTarget* target);
};

