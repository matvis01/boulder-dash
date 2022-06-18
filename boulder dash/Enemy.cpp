#include "Enemy.h"

void Enemy::initVeriables()
{
	this->movementSpeed = 1.5f;
	this->squareSize = 80.f;
	this->isMoving = 0;
	//this->Pos = Vector2f(40.f, 40.f);
	this->lastDir = DOWN;
	
	this->sizeX = 80;
	this->sizeY = 64;
	source = { sizeX, 0, sizeX, sizeY };

	for (int i = 0; i < 4; i++)
	{
		direction[i] = false;
	}
}

void Enemy::setUpSprite()
{
	if (!texture.loadFromFile("assets\\enemy.png"))
	{
		std::cout << "could not load player texture";
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(source);
	sprite.setOrigin(Vector2f(sizeX / 2.f, sizeY / 2.f));
	sprite.setPosition(Pos);
}

Enemy::Enemy(tilePos pos)
{
	this->PosTile = pos;
	this->LastPosTile = PosTile;
	LastPosTile.y--;
	this->initVeriables();
	this->Pos = Vector2f(PosTile.x * 80.f + 40.f, PosTile.y * 80.f + 40.f);
	this->setUpSprite();

}

Enemy::~Enemy()
{
}


void Enemy::movement()
{
	if (isMoving)
	{
		if (direction[LEFT] == true)
		{
			this->sprite.move(-movementSpeed, 0.f);

			//animation
			if (animationClock.getElapsedTime() >= milliseconds(150))
			{
				if (source.left == 0)
				{
					source.left = sizeX * 2;
				}
				else
				{
					source.left -= sizeX;
				}
				sprite.setTextureRect(source);
				animationClock.restart();
			}
			//

			if (this->sprite.getPosition().x <= nextSpot)
			{

				this->sprite.setPosition(nextSpot, this->sprite.getPosition().y);
				isMoving = false;
				direction[LEFT] = false;
				lastDir = LEFT;

			}
		}
		
		else if (direction[UP] == true)
		{
			this->sprite.move(0.f, -movementSpeed);

			//animation
			if (animationClock.getElapsedTime() >= milliseconds(150))
			{
				if (source.left == 0)
				{
					source.left = sizeX * 2;
				}
				else
				{
					source.left -= sizeX;
				}
				sprite.setTextureRect(source);
				animationClock.restart();
			}
			//

			if (this->sprite.getPosition().y <= nextSpot)
			{
				this->sprite.setPosition(this->sprite.getPosition().x, nextSpot);
				isMoving = false;
				direction[UP] = false;
				lastDir = UP;
			}
		}
		else if (direction[RIGHT] == true)
		{
			this->sprite.move(movementSpeed, 0.f);

			//animation
			if (animationClock.getElapsedTime() >= milliseconds(150))
			{
				if (source.left == 0)
				{
					source.left = sizeX * 2;
				}
				else
				{
					source.left -= sizeX;
				}
				sprite.setTextureRect(source);
				animationClock.restart();
			}

			//
			if (this->sprite.getPosition().x >= nextSpot)
			{
				this->sprite.setPosition(nextSpot, this->sprite.getPosition().y);
				isMoving = false;
				direction[RIGHT] = false;
				lastDir = RIGHT;
			}
		}
		else if (direction[DOWN] == true)
		{
			this->sprite.move(0.f, movementSpeed);

			//animation
			if (animationClock.getElapsedTime() >= milliseconds(150))
			{
				if (source.left == 0)
				{
					source.left = sizeX * 2;
				}
				else
				{
					source.left -= sizeX;
				}
				sprite.setTextureRect(source);
				animationClock.restart();
			}
			//
			if (this->sprite.getPosition().y >= nextSpot)
			{
				this->sprite.setPosition(this->sprite.getPosition().x, nextSpot);
				isMoving = false;
				direction[DOWN] = false;
				lastDir = DOWN;
			}
		}
	}
}

void Enemy::updateMovement(bool canGoDir[4])
{
	if (!isMoving)
	{
		/*if (canGoDir[UP] and canGoDir[DOWN] and canGoDir[LEFT] and canGoDir[RIGHT])
		{
			if (lastDir == LEFT)
			{
				source.top = sizeY;
				this->PosTile.x -= 1;
				nextSpot = this->sprite.getPosition().x - this->squareSize;
				direction[LEFT] = true;
				isMoving = true;
			}
			else if (lastDir == RIGHT)
			{
				this->PosTile.x += 1;
				source.top = sizeY * 2;
				nextSpot = this->sprite.getPosition().x + this->squareSize;
				direction[RIGHT] = true;
				isMoving = true;
			}
			else if (lastDir == UP)
			{
				this->PosTile.y -= 1;
				source.top = sizeY * 3;
				nextSpot = this->sprite.getPosition().y - this->squareSize;
				direction[UP] = true;
				isMoving = true;
			}
			else if (lastDir == DOWN)
			{
				this->PosTile.y += 1;
				source.top = 0;
				nextSpot = this->sprite.getPosition().y + this->squareSize;
				direction[DOWN] = true;
				isMoving = true;
			}
		}
		else */if (lastDir == LEFT)
		{
			
			if (canGoDir[UP])
			{
				this->PosTile.y -= 1;
				this->LastPosTile.x -= 1;
				source.top = sizeY * 3;
				nextSpot = this->sprite.getPosition().y - this->squareSize;
				direction[UP] = true;
				isMoving = true;
			}
			else if (canGoDir[LEFT])
			{
				source.top = sizeY;
				this->PosTile.x -= 1;
				this->LastPosTile.x -= 1;
				nextSpot = this->sprite.getPosition().x - this->squareSize;
				direction[LEFT] = true;
				isMoving = true;
			}
			else if (canGoDir[DOWN])
			{
				this->PosTile.y += 1;
				this->LastPosTile.x -= 1;
				source.top = 0;
				nextSpot = this->sprite.getPosition().y + this->squareSize;
				direction[DOWN] = true;
				isMoving = true;
			}
			else if (canGoDir[RIGHT])
			{
				this->PosTile.x += 1;
				this->LastPosTile.x -= 1;
				source.top = sizeY*2;
				nextSpot = this->sprite.getPosition().x + this->squareSize;
				direction[RIGHT] = true;
				isMoving = true;
			}

		}
		else if (lastDir == UP)
		{
			if (canGoDir[RIGHT])
			{
				this->PosTile.x += 1;
				this->LastPosTile.y -= 1;
				source.top = sizeY*2;
				nextSpot = this->sprite.getPosition().x + this->squareSize;
				direction[RIGHT] = true;
				isMoving = true;
			}
			else if (canGoDir[UP])
			{
				this->PosTile.y -= 1;
				this->LastPosTile.y -= 1;
				source.top = sizeY * 3;
				nextSpot = this->sprite.getPosition().y - this->squareSize;
				direction[UP] = true;
				isMoving = true;
			}
			else if (canGoDir[LEFT])
			{
				source.top = sizeY;
				this->PosTile.x -= 1;
				this->LastPosTile.y -= 1;
				nextSpot = this->sprite.getPosition().x - this->squareSize;
				direction[LEFT] = true;
				isMoving = true;
			}
			else if (canGoDir[DOWN])
			{
				this->PosTile.y += 1;
				this->LastPosTile.y -= 1;
				source.top = 0;
				nextSpot = this->sprite.getPosition().y + this->squareSize;
				direction[DOWN] = true;
				isMoving = true;
			}
		}
		else if (lastDir == RIGHT)
		{
			if (canGoDir[DOWN])
			{
				this->PosTile.y += 1;
				this->LastPosTile.x += 1;
				source.top = 0;
				nextSpot = this->sprite.getPosition().y + this->squareSize;
				direction[DOWN] = true;
				isMoving = true;
			}
			else if (canGoDir[RIGHT])
			{
				this->PosTile.x += 1;
				this->LastPosTile.x += 1;
				source.top = sizeY*2;
				nextSpot = this->sprite.getPosition().x + this->squareSize;
				direction[RIGHT] = true;
				isMoving = true;
			}
			else if (canGoDir[UP])
			{
				this->PosTile.y -= 1;
				this->LastPosTile.x += 1;
				source.top = sizeY * 3;
				nextSpot = this->sprite.getPosition().y - this->squareSize;
				direction[UP] = true;
				isMoving = true;
			}
			else if (canGoDir[LEFT])
			{
				source.top = sizeY;
				this->PosTile.x -= 1;
				this->LastPosTile.x += 1;
				nextSpot = this->sprite.getPosition().x - this->squareSize;
				direction[LEFT] = true;
				isMoving = true;
			}
		}
		else if (lastDir == DOWN)
		{
			if (canGoDir[LEFT])
			{
				source.top = sizeY;
				this->PosTile.x -= 1;
				this->LastPosTile.y += 1;
				nextSpot = this->sprite.getPosition().x - this->squareSize;
				direction[LEFT] = true;
				isMoving = true;
			}
			else if (canGoDir[DOWN])
			{
				this->PosTile.y += 1;
				this->LastPosTile.y += 1;
				source.top = 0;
				nextSpot = this->sprite.getPosition().y + this->squareSize;
				direction[DOWN] = true;
				isMoving = true;
			}
			else if (canGoDir[RIGHT])
			{
				this->PosTile.x += 1;
				this->LastPosTile.y += 1;
				source.top = sizeY*2;
				nextSpot = this->sprite.getPosition().x + this->squareSize;
				direction[RIGHT] = true;
				isMoving = true;
			}
			else if (canGoDir[UP])
			{
				this->PosTile.y -= 1;
				this->LastPosTile.y += 1;
				source.top = sizeY * 3;
				nextSpot = this->sprite.getPosition().y - this->squareSize;
				direction[UP] = true;
				isMoving = true;
			}
		}
	}
}

void Enemy::update(bool CanGoDir[4])
{
	this->movement();
	this->updateMovement(CanGoDir);

}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->sprite);
}