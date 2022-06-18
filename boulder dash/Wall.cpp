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

bool Wall::getIsMovingSideways()
{
	return false;
}

bool Wall::moveSideways(bool movesLeft, float speed)
{
	return false;
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
	this->textureFile = { "assets\\wall5.png" };
	this->isPassable = 0;
}