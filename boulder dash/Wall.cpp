#include "Wall.h"


bool Wall::fallDown()
{
	return false;
}

bool Wall::fallLeft()
{
	return false;
}

bool Wall::fallRight()
{
	return false;
}

bool Wall::getIsMoving()
{
	return false;
}

void Wall::changeIsMoving()
{
}

Wall::Wall(float x, float y)
{
	position = Vector2f(x, y);

	this->sprite.setPosition(position);
	SetupVariables();
	SetupSprite();
}

Wall::~Wall()
{
}

void Wall::SetupVariables()
{
	this->name = Name::wall;
	this->textureFile = { "assets\\wall.png" };
	this->isPassable = 0;
}