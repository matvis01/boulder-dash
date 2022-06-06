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

	//this->sprite.setScale(Vector2f(1.5, 1.5));
}

Player::Player()
{
	this->initVeriables();

	this->sprite.setPosition(playerPos);

	if (!texture.loadFromFile("assets\\player.png"))
	{
		std::cout << "could not load player texture";
	}
	sprite.setTexture(texture);

	if (!buffer.loadFromFile("sounds\\uff.wav"))
	{
		std::cout << "cant load hit sound";
	}
	hitSound.setBuffer(buffer);
	
	this->setSize();
}

Vector2f Player::getPlayerPos()
{
	return sprite.getPosition();
}

float Player::getPlayerSpeed()
{
	return movementSpeed;
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
			this->sprite.move(-movementSpeed, 0.f);
			movedLeft = true;

			if (this->sprite.getPosition().x <= nextSpot)
			{
				
				this->sprite.setPosition(nextSpot,this->sprite.getPosition().y);
				isMoving = false;
				direction[LEFT] = false;
			}
		}
		else if (direction[RIGHT] == true)
		{
			this->sprite.move(movementSpeed, 0.f);
			movedLeft = false;

			if (this->sprite.getPosition().x >= nextSpot)
			{
				this->sprite.setPosition(nextSpot, this->sprite.getPosition().y);
				isMoving = false;
				direction[RIGHT] = false;
			}
		}
		else if (direction[UP] == true)
		{
			this->sprite.move(0.f,-movementSpeed);

			if (this->sprite.getPosition().y <= nextSpot)
			{
				this->sprite.setPosition(this->sprite.getPosition().x,nextSpot);
				isMoving = false;
				direction[UP] = false;
			}
		}
		else if (direction[DOWN] == true)
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
		if ((Keyboard::isKeyPressed(Keyboard::A)) or (Keyboard::isKeyPressed(Keyboard::Left)))
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
		else if ((Keyboard::isKeyPressed(Keyboard::D)) or (Keyboard::isKeyPressed(Keyboard::Right)))
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
		else if ((Keyboard::isKeyPressed(Keyboard::S)) or (Keyboard::isKeyPressed(Keyboard::Down)))
		{
			if (canMoveDown)
			{
				this->playerPosTile.y += 1;

				nextSpot = this->sprite.getPosition().y + this->squareSize;
				direction[DOWN] = true;
				isMoving = true;
			}
			
		}
		else if ((Keyboard::isKeyPressed(Keyboard::W)) or (Keyboard::isKeyPressed(Keyboard::Up)))
		{
			if (canMoveUp)
			{
				this->playerPosTile.y -= 1;

				nextSpot = this->sprite.getPosition().y - this->squareSize;
				direction[UP] = true;
				isMoving = true;
			}
		}
	}
}

void Player::setPlayerPos(tilePos startingPos)
{
	playerPosTile = startingPos;
	playerPos = Vector2f(startingPos.x * 80.f + 40.f, startingPos.y * 80.f + 40.f);
	sprite.setPosition(playerPos);
}

void Player::playHitSound()
{
	hitSound.play();
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

