#include "EndLvl.h"

bool EndLvl::fallDown()
{
	return false;
}

bool EndLvl::fallLeft()
{
	return false;
}

bool EndLvl::fallRight()
{
	return false;
}

bool EndLvl::getIsMoving()
{
	return false;
}

void EndLvl::changeIsMoving()
{
}

bool EndLvl::getIsMovingSideways()
{
	return false;
}

bool EndLvl::moveSideways(bool movesLeft, float speed)
{
	return false;
}

EndLvl::EndLvl(float x, float y)
{
	position = Vector2f(x, y);

	this->sprite.setPosition(position);
	SetupVariables();
	SetupSprite();
}

EndLvl::~EndLvl()
{
}

void EndLvl::SetupVariables()
{
	this->name = Name::endlvl;
	this->textureFile = { "assets\\endlvl.png" };
	this->isPassable = 1;
}
