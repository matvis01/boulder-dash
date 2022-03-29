#include "Ground.h"

bool Ground::fallDown()
{
	return false;
}

bool Ground::fallLeft()
{
	return false;
}

bool Ground::fallRight()
{
	return false;
}

bool Ground::getIsMoving()
{
	return false;
}

void Ground::changeIsMoving()
{
}

Ground::Ground(float x, float y)
{
	position = Vector2f(x, y);

	this->sprite.setPosition(position);
	SetupVariables();
	SetupSprite();
}

Ground::~Ground()
{
}

void Ground::SetupVariables()
{
	this->name = "Ground";
	this->textureFile = { "assets\\ground.png" };
	this->isPassable = 1;
}
