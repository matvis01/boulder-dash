#include "Rock.h"

Rock::Rock(float x, float y)
{
	position = Vector2f(x, y);

	this->sprite.setPosition(position);
	SetupVariables();
	SetupSprite();
}

Rock::~Rock()
{
}

void Rock::SetupVariables()
{
	this->name = Name::rock;
	this->textureFile =  "assets\\rock3.png" ;
	this->isPassable = 0;
	this->isMoving = 0;
	this->movable = 1;
	this->isMovingSideways = 0;
}

void Rock::changeIsMoving()
{
	this->isMoving = false;
}

bool Rock::fallDown()// tries to make object fall down
{

	if (!isMoving)
	{
		nextSpot = sprite.getPosition().y + tileSize;
		this->isMoving = true;
		return false;
	}
	else
	{
		this->sprite.move(0.f, 2.f);

		if (sprite.getPosition().y >= nextSpot)
		{
			sprite.setPosition(sprite.getPosition().x, nextSpot);

			return true;
		}
		else
			return false;
	}
}

bool Rock::getIsMoving()
{
	return isMoving;
}

bool Rock::getIsMovingSideways()
{
	return isMovingSideways;
}

bool Rock::fallLeft()
{
	if (!isMoving)
	{
		this->nextSpot = sprite.getPosition().y + tileSize;
		this->nextSpotSide = sprite.getPosition().x - tileSize;
		this->isMoving = true;
		return false;
	}
	else
	{
		if (sprite.getPosition().x > nextSpotSide)
		{
			this->sprite.move(-2.f, 1/2.f);
			sprite.rotate(-2.f);
		}
		else
		{
			this->sprite.move(0.f, 2.f);
		}

		if (sprite.getPosition().y >= nextSpot)
		{
			this->sprite.setPosition(nextSpotSide, nextSpot);

			return true;
		}
		else
			return false;
		

	}
}

bool Rock::fallRight()
{
	if (!isMoving)
	{
		this->nextSpot = sprite.getPosition().y + tileSize;
		this->nextSpotSide = sprite.getPosition().x + tileSize;
		this->isMoving = true;
		return false;
	}
	else
	{

		if (sprite.getPosition().x < this->nextSpotSide)
		{
			this->sprite.move(2.f, 1 / 2.f);
			sprite.rotate(2.f);
		}
		else
		{
			this->sprite.move(0.f, 2.f);
		}

		if (sprite.getPosition().y >= nextSpot)
		{
			this->sprite.setPosition(this->nextSpotSide, this->nextSpot);

			return true;
		}
		else
			return false;


	}
}

bool Rock::moveSideways(bool movesLeft , float speed)
{
	if (movesLeft)
	{
		if (!isMovingSideways)
		{
			nextSpot = sprite.getPosition().x - tileSize;
			this->isMovingSideways = true;
			return false;
		}
		else
		{
			this->sprite.move(-(speed+(1/10.f)), 0.f);
			sprite.rotate(-3.f);

			if (sprite.getPosition().x <= nextSpot)
			{
				sprite.setPosition(nextSpot, sprite.getPosition().y);
				this->isMovingSideways = false;

				return true;
			}
			else
				return false;
		}
	}
	else
	{
		if (!isMovingSideways)
		{
			nextSpot = sprite.getPosition().x + tileSize;
			this->isMovingSideways = true;
			return false;
		}
		else
		{
			this->sprite.move(speed+(1 / 10.f), 0.f);
			sprite.rotate(3.f);

			if (sprite.getPosition().x >= nextSpot)
			{
				sprite.setPosition(nextSpot, sprite.getPosition().y);
				this->isMovingSideways = false;
				return true;
			}
			else
				return false;
		}
	}
}
