#include "Player.h"

void Player::initVeriables()
{
	this->movementSpeed = 3.f;
	this->squareSize = 80.f;
	this->isMoving = 0;
	this->playerPos = Vector2f(40.f, 40.f);
	this->playerPosTile.x = 0;
	this->playerPosTile.y = 0;

	for (int i = 0; i < 4; i++)
	{
		direction[i] = false;
	}
}

void Player::setSize()
{

	sprite.setOrigin(Vector2f(40.f, 40.f));

	//this->sprite.setScale(Vector2f(scalex, scaley));

}

Player::Player()
{
	this->initVeriables();

	this->sprite.setPosition(playerPos);

	if (!texture.loadFromFile("assets\\amogus.png"))
	{
		std::cout << "could not load player texture";
	}
	sprite.setTexture(texture);

	
	this->setSize();
}

Vector2f Player::getPlayerPos()
{
	return sprite.getPosition();
}

Player::~Player()
{
}


void Player::movement()
{
	if (isMoving)
	{
		if (direction[LEFT] == true)
		{
			//this->sprite.setScale(-1.f, 1.f);

			this->sprite.move(-movementSpeed, 0.f);

			if (this->sprite.getPosition().x <= nextSpot)
			{

				this->sprite.setPosition(nextSpot,this->sprite.getPosition().y);
				isMoving = false;
				direction[LEFT] = false;
			}
		}
		if (direction[RIGHT] == true)
		{
			//this->sprite.setScale(1.f, 1.f);

			this->sprite.move(movementSpeed, 0.f);

			if (this->sprite.getPosition().x >= nextSpot)
			{
				this->sprite.setPosition(nextSpot, this->sprite.getPosition().y);
				isMoving = false;
				direction[RIGHT] = false;


			}
		}
		if (direction[UP] == true)
		{
			this->sprite.move(0.f,-movementSpeed);


			if (this->sprite.getPosition().y <= nextSpot)
			{
				this->sprite.setPosition(this->sprite.getPosition().x,nextSpot);
				isMoving = false;
				direction[UP] = false;


			}
		}
		if (direction[DOWN] == true)
		{
			this->sprite.move(0.f, movementSpeed);

			if (this->sprite.getPosition().y >= nextSpot)
			{
				this->sprite.setPosition(this->sprite.getPosition().x, nextSpot);
				isMoving = false;
				direction[DOWN] = false;


			}
		}
	}
}

void Player::updateInput(bool canMoveLeft, bool canMoveRight, bool canMoveDown, bool canMoveUp)
{
	if (!isMoving)
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			this->sprite.setScale(-1.f, 1.f);
			if (canMoveLeft)
			{
				this->playerPosTile.x -= 1;

				nextSpot = this->sprite.getPosition().x - this->squareSize;
				direction[LEFT] = true;
				isMoving = true;
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			this->sprite.setScale(1.f, 1.f);
			if (canMoveRight)
			{
				this->playerPosTile.x += 1;

				nextSpot = this->sprite.getPosition().x + this->squareSize;
				direction[RIGHT] = true;
				isMoving = true;
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) and canMoveDown)
		{
			this->playerPosTile.y += 1;

			nextSpot = this->sprite.getPosition().y + this->squareSize;
			direction[DOWN] = true;
			isMoving = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::W) and canMoveUp)
		{
			this->playerPosTile.y -= 1;

			nextSpot = this->sprite.getPosition().y - this->squareSize;
			direction[UP] = true;
			isMoving = true;
		}
	}
}

void Player::update(bool canMoveLeft, bool canMoveRight, bool canMoveDown, bool canMoveUp)
{
	this->updateInput(canMoveLeft, canMoveRight, canMoveDown, canMoveUp);
	this->movement();
}



void Player::render(RenderTarget* target)
{
	target->draw(this->sprite);
}

