#include "Game.h"



void Game::initVariables()
{
	this->endGame = false;
	this->viewIsMoving = false;

	for (int i = 0; i < 4; i++)
	{
		viewMoveDirection[i] = false;
	}
}

void Game::initWindow()
{
	this->videoMode = VideoMode(1280, 960);
	this->window = new RenderWindow(this->videoMode, "boulder dash", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(144);
}



bool Game::canMoveLeft()
{
	if (player.playerPosTile.x > 0) // cant go outside of map
	{
		if (this->level.tiles[player.playerPosTile.x - 1][player.playerPosTile.y] != nullptr)
		{
			if (this->level.tiles[player.playerPosTile.x - 1][player.playerPosTile.y]->isPassable == false)
			{
				return false;
			}
			else 
				return true;
		}
		else
			return true;
	}
	else
	 return false;
}

bool Game::canMoveRight()
{
	if (player.playerPosTile.x < level.mapSizeX) // cant go outside of map
	{
		if (this->level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y] != nullptr)
		{
			if (this->level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y]->isPassable == false)
			{
				return false;
			}
			else
				return true;
		}
		else
			return true;
	}
	else
		return false;
}

bool Game::canMoveUp()
{
	if (player.playerPosTile.y > 0) // cant go outside of map
	{
		if (this->level.tiles[player.playerPosTile.x][player.playerPosTile.y - 1] != nullptr)
		{
			if (this->level.tiles[player.playerPosTile.x][player.playerPosTile.y - 1]->isPassable == false)
			{
				return false;
			}
			else
				return true;
		}
		else
			return true;
	}
	else
		return false;
}

bool Game::canMoveDown()
{
	if (player.playerPosTile.y < level.mapSizeY) // cant go outside of map
	{
		if (this->level.tiles[player.playerPosTile.x][player.playerPosTile.y + 1] != nullptr)
		{
			if (this->level.tiles[player.playerPosTile.x][player.playerPosTile.y + 1]->isPassable == false)
			{
				return false;
			}
			else
				return true;
		}
		else
			return true;
	}
	else
		return false;
}

void Game::initView()
{
	this->view.setSize(1280.f, 960.f);
	this->view.setCenter(1280 / 2.f, 960 / 2.f);
}

void Game::moveView()
{
	if (viewIsMoving)
	{
		if (viewMoveDirection[DOWN])
		{
			this->view.move(0.f, 4.f);

			if (this->view.getCenter().y >= viewNextSpoty)
			{
				viewIsMoving = false;
				viewMoveDirection[DOWN] = false;
			}

		}
		if (viewMoveDirection[UP])
		{
			this->view.move(0.f, -4.f);

			if (this->view.getCenter().y <= viewNextSpoty)
			{
				viewIsMoving = false;
				viewMoveDirection[UP] = false;
			}
		}
		if (viewMoveDirection[RIGHT])
		{
			this->view.move(4.f, 0.f);

			if (this->view.getCenter().x >= viewNextSpotx)
			{
				viewIsMoving = false;
				viewMoveDirection[RIGHT] = false;
			}
		}
		if (viewMoveDirection[LEFT])
		{
			this->view.move(-4.f, 0.f);

			if (this->view.getCenter().x <= viewNextSpotx)
			{
				viewIsMoving = false;
				viewMoveDirection[LEFT] = false;
			}
		}
	}
}



void Game::tryViewMove()
{
	if (this->player.getPlayerPos().y > 320.f and this->player.getPlayerPos().y < 1640.f) // dodac konce poziomu (and pos<costam.f)
	{
		
		if (this->player.getPlayerPos().y - 4 * 80.f >= view.getCenter().y)
		{
			viewNextSpoty = view.getCenter().y + 320.F;

			viewMoveDirection[DOWN] = true;
			viewIsMoving = true;
		}
		if (this->player.getPlayerPos().y + 4 * 80.f <= view.getCenter().y)
		{
			viewNextSpoty = view.getCenter().y - 320.f;

			viewMoveDirection[UP] = true;
			viewIsMoving = true;
		}
	}
	if(this->player.getPlayerPos().x > 400.f) // dodac konce poziomu 
	{
		if (this->player.getPlayerPos().x - 4 * 80.f >= view.getCenter().x)
		{
			viewNextSpotx = view.getCenter().x + 400.f;

			viewMoveDirection[RIGHT] = true;
			viewIsMoving = true;
		}
		if (this->player.getPlayerPos().x + 4 * 80.f <= view.getCenter().x)
		{
			viewNextSpotx = view.getCenter().x - 400.f;

			viewMoveDirection[LEFT] = true;
			viewIsMoving = true;
		}
		
	}
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initView();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		if (sfmlEvent.type == Event::Closed) this->window->close();

		if (sfmlEvent.type == Event::KeyPressed)
		{
			if (this->sfmlEvent.key.code == Keyboard::Escape) this->window->close();
		}
	}
}

void Game::removeGround()
{
	if (level.tiles[player.playerPosTile.x][player.playerPosTile.y] != nullptr)
	{
		if (level.tiles[player.playerPosTile.x][player.playerPosTile.y]->isPassable) // add destructor
		{
			level.tiles[player.playerPosTile.x][player.playerPosTile.y]->~GameTile();
			this->level.tiles[player.playerPosTile.x][player.playerPosTile.y] = nullptr;
		}
	}
}


void Game::findRock()
{
	for (int i = 0; i < this->level.mapSizeY-1; i++)
	{
		for (int j = 0; j < level.mapSizeX-1; j++)
		{
			if (level.tiles[j][i] != nullptr and level.tiles[j][i]->getName() == "Rock")
			{
				if (level.tiles[j][i+1] == nullptr) // falls down
				{
					if (player.playerPosTile.x == j and player.playerPosTile.y == i + 1 and level.tiles[j][i] != nullptr and level.tiles[j][i]->getIsMoving())
					{
						std::cout << "player dies !!!!!!!!!!!!!!!!!!!!! \n";
					}

					if (!(player.playerPosTile.x == j and player.playerPosTile.y == i + 1))
					{

						if (level.tiles[j][i]->fallDown())
						{

							if (player.playerPosTile.x == j and player.playerPosTile.y == i + 2 and level.tiles[j][i] != nullptr and level.tiles[j][i]->getIsMoving())
							{
								std::cout << "player dies !!!!!!!!!!!!!!!!!!!!! \n";
							}

							level.tiles[j][i]->changeIsMoving();

							level.tiles[j][i + 1] = level.tiles[j][i];
							level.tiles[j][i] = nullptr;
						}
					}
				}
				else if (level.tiles[j][i + 1] != nullptr and level.tiles[j][i + 1]->getName() == "Rock")
				{
					if (j >= 1 and level.tiles[j - 1][i] == nullptr and level.tiles[j - 1][i + 1] == nullptr) // left free
					{
						if (!(player.playerPosTile.x == j - 1 and player.playerPosTile.y == i or player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 1)) // player not blocking left
						{
							if (level.tiles[j][i]->fallLeft())
							{

								if ((player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 2 or player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 1) and level.tiles[j][i] != nullptr and level.tiles[j][i]->getIsMoving())
								{
									std::cout << "player dies left !!!!!!!!!!!!!!!!!!!!! \n";
								}

								level.tiles[j][i]->changeIsMoving();

								level.tiles[j - 1][i + 1] = level.tiles[j][i];
								level.tiles[j][i] = nullptr;
							}
						}
						else if(level.tiles[j][i]->getIsMoving())
							std::cout << "player dies  left !!!!!!!!!!!!!!!!!!!!! \n";
					}
					
				}
			}
		}
	}
}

void Game::update()
{
	this->pollEvents();
	this->player.update(canMoveLeft(),canMoveRight(), canMoveDown(), canMoveUp());
	removeGround();
	findRock();
	tryViewMove();
	moveView();
}

void Game::render()
{
	this->window->clear();
	
	// stuff to render
	this->window->setView(view);
	this->level.render(this->window);
	this->player.render(this->window);
	//
	this->window->display();
}
