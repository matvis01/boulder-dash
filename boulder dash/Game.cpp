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
			if (player.playerPosTile.x >= 2 and this->level.tiles[player.playerPosTile.x - 1][player.playerPosTile.y]->getName() == Name::rock and this->level.tiles[player.playerPosTile.x - 2][player.playerPosTile.y] == nullptr)
			{// single rock on left
				return true;
			}
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
	if (player.playerPosTile.x < level.mapSizeX-1) // cant go outside of map
	{
		if (this->level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y] != nullptr)
		{
			if (player.playerPosTile.x < level.mapSizeX - 2 and this->level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y]->getName() == Name::rock and this->level.tiles[player.playerPosTile.x + 2][player.playerPosTile.y] == nullptr)
			{// single rock on right
				return true;
			}
			if (this->level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y]->isPassable == false)
			{// not passable on right
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
	if (player.playerPosTile.y < level.mapSizeY-1) // cant go outside of map
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

void Game::tryMoveRockSideways()
{
	if (level.tiles[player.playerPosTile.x][player.playerPosTile.y] != nullptr and level.tiles[player.playerPosTile.x][player.playerPosTile.y]->getName() == Name::rock)
	{// player is on a rock
		if (this->player.direction[LEFT])// player moves left
		{
			if (level.tiles[player.playerPosTile.x][player.playerPosTile.y]->moveSideways(true, player.getPlayerSpeed()))
			{
				level.tiles[player.playerPosTile.x - 1][player.playerPosTile.y] = level.tiles[player.playerPosTile.x][player.playerPosTile.y];
				level.tiles[player.playerPosTile.x][player.playerPosTile.y] = nullptr;
			}
		}
		else if (this->player.direction[RIGHT])//player moves right
		{
			if (level.tiles[player.playerPosTile.x][player.playerPosTile.y]->moveSideways(false, player.getPlayerSpeed()))
			{
				level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y] = level.tiles[player.playerPosTile.x][player.playerPosTile.y];
				level.tiles[player.playerPosTile.x][player.playerPosTile.y] = nullptr;
			}
		}
	}
}

void Game::findFallable()
{
	for (int i = 0; i < this->level.mapSizeY-1; i++)
	{
		for (int j = 0; j < level.mapSizeX-1; j++)
		{
			if(i >= 1 and level.tiles[j][i - 1] != nullptr and level.tiles[j][i - 1]->getName() == Name::rock and level.tiles[j][i - 1]->getIsMoving())
			{ // cant fall if one above falls
				break;
			}
			if (i >= 1 and j >= 1 and level.tiles[j-1][i - 1] != nullptr and level.tiles[j-1][i - 1]->getName() == Name::rock and level.tiles[j-1][i - 1]->getIsMoving())
			{ // cant fall if one above on the left falls
				break;
			}
			if (i >= 1 and j < level.mapSizeX-2 and level.tiles[j + 1][i - 1] != nullptr and level.tiles[j + 1][i - 1]->getName() == Name::rock and level.tiles[j+1][i - 1]->getIsMoving())
			{ // cant fall if one above on the left falls
				break;
			}
			if (level.tiles[j][i] != nullptr and level.tiles[j][i]->getName() == Name::rock)
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
				else if (level.tiles[j][i + 1] != nullptr and level.tiles[j][i + 1]->getName() == Name::rock and !level.tiles[j][i+1]->getIsMoving())
				{
					
					if (j >= 1 and level.tiles[j - 1][i] == nullptr and level.tiles[j - 1][i + 1] == nullptr) // left free
					{
						if (j >= 1 and level.tiles[j + 1][i] == nullptr and level.tiles[j + 1][i + 1] == nullptr) //right free
						{
						// both sides free
							if (!(player.playerPosTile.x == j + 1 and player.playerPosTile.y == i or player.playerPosTile.x == j + 1 and player.playerPosTile.y == i + 1) and !(player.playerPosTile.x == j - 1 and player.playerPosTile.y == i or player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 1))
							{// player not blocking left or right

								if (lastFellLeft) // falls right
								{
									if ((player.playerPosTile.x == j + 1 and player.playerPosTile.y == i or player.playerPosTile.x == j + 1 and player.playerPosTile.y == i + 1) and level.tiles[j][i]->getIsMoving())// gracz umiera
									{// player on right
										std::cout << "player dies  right !!!!!!!!!!!!!!!!!!!!! \n";
									}
									if (level.tiles[j][i]->fallRight())
									{
										if ((player.playerPosTile.x == j + 1 and player.playerPosTile.y == i + 2 or player.playerPosTile.x == j + 1 and player.playerPosTile.y == i + 1) and level.tiles[j][i] != nullptr and level.tiles[j][i]->getIsMoving()) // should player die
										{
											std::cout << "player dies right !!!!!!!!!!!!!!!!!!!!! \n";
										}
										level.tiles[j][i]->changeIsMoving();
										lastFellLeft = false;

										level.tiles[j + 1][i + 1] = level.tiles[j][i];
										level.tiles[j][i] = nullptr;
									}

								}
								else // falls left
								{
									if ((player.playerPosTile.x == j - 1 and player.playerPosTile.y == i or player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 1) and level.tiles[j][i]->getIsMoving())
									{ // player on left
										std::cout << "player dies  left !!!!!!!!!!!!!!!!!!!!! \n";
									}
									if (level.tiles[j][i]->fallLeft())
									{
										if ((player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 2 or player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 1) and level.tiles[j][i] != nullptr and level.tiles[j][i]->getIsMoving())
										{
											std::cout << "player dies left !!!!!!!!!!!!!!!!!!!!! \n";
										}
										level.tiles[j][i]->changeIsMoving();
										lastFellLeft = true;

										level.tiles[j - 1][i + 1] = level.tiles[j][i];
										level.tiles[j][i] = nullptr;
									}
								}
							}
							else if (!(player.playerPosTile.x == j + 1 and player.playerPosTile.y == i or player.playerPosTile.x == j + 1 and player.playerPosTile.y == i + 1))
							{ // player is not on right
								if (level.tiles[j][i]->fallRight())
								{
									if ((player.playerPosTile.x == j + 1 and player.playerPosTile.y == i + 2 or player.playerPosTile.x == j + 1 and player.playerPosTile.y == i + 1) and level.tiles[j][i] != nullptr and level.tiles[j][i]->getIsMoving()) // should player die
									{
										std::cout << "player dies right !!!!!!!!!!!!!!!!!!!!! \n";
									}
									level.tiles[j][i]->changeIsMoving();
									lastFellLeft = false;

									level.tiles[j + 1][i + 1] = level.tiles[j][i];
									level.tiles[j][i] = nullptr;
								}
							}
							else if (!(player.playerPosTile.x == j - 1 and player.playerPosTile.y == i or player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 1)) // player not blocking left
							{
								if ((player.playerPosTile.x == j - 1 and player.playerPosTile.y == i or player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 1) and level.tiles[j][i]->getIsMoving())
								{ // player on left
									std::cout << "player dies  left !!!!!!!!!!!!!!!!!!!!! \n";
								}
								if (level.tiles[j][i]->fallLeft())
								{
									if ((player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 2 or player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 1) and level.tiles[j][i] != nullptr and level.tiles[j][i]->getIsMoving())
									{
										std::cout << "player dies left !!!!!!!!!!!!!!!!!!!!! \n";
									}
									level.tiles[j][i]->changeIsMoving();
									lastFellLeft = true;

									level.tiles[j - 1][i + 1] = level.tiles[j][i];
									level.tiles[j][i] = nullptr;
								}
							}
						}
						else if (!(player.playerPosTile.x == j - 1 and player.playerPosTile.y == i or player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 1)) // player not blocking left
						{
							if (level.tiles[j][i]->fallLeft())
							{
								if ((player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 2 or player.playerPosTile.x == j - 1 and player.playerPosTile.y == i + 1) and level.tiles[j][i] != nullptr and level.tiles[j][i]->getIsMoving())
								{
									std::cout << "player dies left !!!!!!!!!!!!!!!!!!!!! \n";
								}
								level.tiles[j][i]->changeIsMoving();
								lastFellLeft = true;

								level.tiles[j - 1][i + 1] = level.tiles[j][i];
								level.tiles[j][i] = nullptr;
							}
						}
						else if(level.tiles[j][i]->getIsMoving())
							std::cout << "player dies  left !!!!!!!!!!!!!!!!!!!!! \n";
					}
					else if (j >= 1 and level.tiles[j + 1][i] == nullptr and level.tiles[j + 1][i + 1] == nullptr)//only right free
					{
						if ((player.playerPosTile.x == j + 1 and player.playerPosTile.y == i or player.playerPosTile.x == j + 1 and player.playerPosTile.y == i + 1) and level.tiles[j][i]->getIsMoving())// gracz umiera
						{// player on right
							std::cout << "player dies  right !!!!!!!!!!!!!!!!!!!!! \n";
						}
						if (!(player.playerPosTile.x == j + 1 and player.playerPosTile.y == i or player.playerPosTile.x == j + 1 and player.playerPosTile.y == i + 1))
						{
							if (level.tiles[j][i]->fallRight())
							{
								if ((player.playerPosTile.x == j + 1 and player.playerPosTile.y == i + 2 or player.playerPosTile.x == j + 1 and player.playerPosTile.y == i + 1) and level.tiles[j][i] != nullptr and level.tiles[j][i]->getIsMoving()) // should player die
								{
									std::cout << "player dies right !!!!!!!!!!!!!!!!!!!!! \n";
								}
								level.tiles[j][i]->changeIsMoving();
								lastFellLeft = false;

								level.tiles[j + 1][i + 1] = level.tiles[j][i];
								level.tiles[j][i] = nullptr;
							}
						}
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
	findFallable();
	tryMoveRockSideways();
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
