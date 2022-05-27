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
	this->textureFile =  "assets\\rock.png" ;
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
		std::cout << "not moving"<<std::endl;
		nextSpot = sprite.getPosition().y + tileSize;
		this->isMoving = true;
		return false;
	}
	else
	{
		std::cout << "moves" << std::endl;
		this->sprite.move(0.f, 2.f);

		if (sprite.getPosition().y >= nextSpot)
		{
			sprite.setPosition(sprite.getPosition().x, nextSpot);
			//this->isMoving = false;
			std::cout << "on new pos" << std::endl;


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
		std::cout << "not moving left" << std::endl;
		this->nextSpot = sprite.getPosition().y + tileSize;
		this->nextSpotSide = sprite.getPosition().x - tileSize;
		this->isMoving = true;
		return false;
	}
	else
	{
		std::cout << "moves left" << std::endl;

		if (sprite.getPosition().x > nextSpotSide)
		{
			this->sprite.move(-2.f, 1/2.f);
		}
		else
		{
			this->sprite.move(0.f, 2.f);
		}

		if (sprite.getPosition().y >= nextSpot)
		{
			this->sprite.setPosition(nextSpotSide, nextSpot);
			//this->isMoving = false;
			std::cout << "on new pos left" << std::endl;


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
		std::cout << "not moving left" << std::endl;
		this->nextSpot = sprite.getPosition().y + tileSize;
		this->nextSpotSide = sprite.getPosition().x + tileSize;
		this->isMoving = true;
		return false;
	}
	else
	{
		std::cout << "moves left" << std::endl;

		if (sprite.getPosition().x < this->nextSpotSide)
		{
			this->sprite.move(2.f, 1 / 2.f);
		}
		else
		{
			this->sprite.move(0.f, 2.f);
		}

		if (sprite.getPosition().y >= nextSpot)
		{
			this->sprite.setPosition(this->nextSpotSide, this->nextSpot);
			//this->isMoving = false;
			std::cout << "on new pos left" << std::endl;


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
			std::cout << "not moving" << std::endl;
			nextSpot = sprite.getPosition().x - tileSize;
			this->isMovingSideways = true;
			return false;
		}
		else
		{
			std::cout << "moves left" << std::endl;
			this->sprite.move(-(speed+(1/10.f)), 0.f);

			if (sprite.getPosition().x <= nextSpot)
			{
				sprite.setPosition(nextSpot, sprite.getPosition().y);
				this->isMovingSideways = false;
				std::cout << "on new pos left" << std::endl;

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
			std::cout << "not moving" << std::endl;
			nextSpot = sprite.getPosition().x + tileSize;
			this->isMovingSideways = true;
			return false;
		}
		else
		{
			std::cout << "moves right" << std::endl;
			this->sprite.move(speed+(1 / 10.f), 0.f);

			if (sprite.getPosition().x >= nextSpot)
			{
				sprite.setPosition(nextSpot, sprite.getPosition().y);
				this->isMovingSideways = false;
				std::cout << "on new pos right" << std::endl;

				return true;
			}
			else
				return false;
		}
	}
}
