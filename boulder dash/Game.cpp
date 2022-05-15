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
			if (player.playerPosTile.x >= 2 and this->level.tiles[player.playerPosTile.x - 1][player.playerPosTile.y]->getName() == Name::rock and this->level.tiles[player.playerPosTile.x - 2][player.playerPosTile.y] == nullptr and this->level.tiles[player.playerPosTile.x-1 ][player.playerPosTile.y+1] != nullptr)
			{// single rock on left
				if (this->level.tiles[player.playerPosTile.x - 1][player.playerPosTile.y]->getIsMoving())
					return false;
				else
					return true;
			}
			if (this->level.tiles[player.playerPosTile.x - 1][player.playerPosTile.y]->isPassable)
			{
				return true;
			}
			else 
				return false;
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
		if (this->level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y] != nullptr )
		{
			if (player.playerPosTile.x < level.mapSizeX - 2 and this->level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y]->getName() == Name::rock and this->level.tiles[player.playerPosTile.x + 2][player.playerPosTile.y] == nullptr and this->level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y + 1] != nullptr)
			{// single rock on right
				if (this->level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y]->getIsMoving())
					return false;
				else
					return true;
			}
			if (this->level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y]->isPassable)
			{// not passable on right
				return true;
			}
			else
				return false;
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

void Game::playerOnGameTile()
{
	if (level.tiles[player.playerPosTile.x][player.playerPosTile.y] != nullptr)
	{
		if (level.tiles[player.playerPosTile.x][player.playerPosTile.y]->getName() == Name::ground)
		{
			this->level.tiles[player.playerPosTile.x][player.playerPosTile.y] = nullptr;
		}
		else if (level.tiles[player.playerPosTile.x][player.playerPosTile.y]->getName() == Name::diamond)
		{
			level.diamondsCollected += 1;
			this->level.tiles[player.playerPosTile.x][player.playerPosTile.y] = nullptr;
		}
		else if (level.tiles[player.playerPosTile.x][player.playerPosTile.y]->getName() == Name::endlvl and level.diamondsCollected >= level.diamondsRequired)
		{// on EndLvl tile and collected enough diamonds
			if (level.currentLevel < level.howManyLevels)
			{// change to next level
				if (!player.isMoving)
				{
					level.currentLevel += 1;
					level.clearLevel();
					level.chooseLevel();
					player.setPlayerPos(level.playerStartingPos);
					view.setCenter(1280 / 2.f, 960 / 2.f);
				}
			}
			else
			{
				std::cout << "game finished" << std::endl;
			}

		}
	}
}

void Game::tryMoveRockSideways()
{
	if (level.tiles[player.playerPosTile.x][player.playerPosTile.y] != nullptr and level.tiles[player.playerPosTile.x][player.playerPosTile.y]->getName() == Name::rock)
	{// player is on a rock
		if (!level.tiles[player.playerPosTile.x][player.playerPosTile.y]->isMoving)
		{
			if (this->player.movedLeft)// player moves left
			{
				if (level.tiles[player.playerPosTile.x][player.playerPosTile.y]->moveSideways(true, player.getPlayerSpeed()))
				{
					level.tiles[player.playerPosTile.x][player.playerPosTile.y]->tilePosition.x -= 1;
					level.tiles[player.playerPosTile.x - 1][player.playerPosTile.y] = level.tiles[player.playerPosTile.x][player.playerPosTile.y];
					level.tiles[player.playerPosTile.x][player.playerPosTile.y] = nullptr;
				}
			}
			else//player moves right
			{
				if (level.tiles[player.playerPosTile.x][player.playerPosTile.y]->moveSideways(false, player.getPlayerSpeed()))
				{
					level.tiles[player.playerPosTile.x][player.playerPosTile.y]->tilePosition.x += 1;
					level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y] = level.tiles[player.playerPosTile.x][player.playerPosTile.y];
					level.tiles[player.playerPosTile.x][player.playerPosTile.y] = nullptr;
				}
			}
		}
	}
}

void Game::keyboardInputs()
{
	if (Keyboard::isKeyPressed(Keyboard::R))
	{
		if (!viewIsMoving and !player.isMoving)
		{
			level.clearLevel();
			level.chooseLevel();
			player.setPlayerPos(level.playerStartingPos);
			view.setCenter(1280 / 2.f, 960 / 2.f);
		}
	}
}

void Game::findFallable()
{
	for (int v = 0; v < level.allFallable.size(); v++)
	{
		int y, x;
		x = this->level.allFallable[v]->tilePosition.x;
		y = this->level.allFallable[v]->tilePosition.y;

		if (x >= 0 and x < level.mapSizeX-1 and y >= 0 and y < level.mapSizeY-1)
		{
			if (!(y >= 1 and level.tiles[x][y - 1] != nullptr and level.tiles[x][y - 1]->movable and level.tiles[x][y - 1]->getIsMoving()) and !(y >= 1 and x >= 1 and level.tiles[x - 1][y - 1] != nullptr and level.tiles[x - 1][y - 1]->movable and level.tiles[x - 1][y - 1]->getIsMoving()) and !(y >= 1 and x < level.mapSizeX - 2 and level.tiles[x + 1][y - 1] != nullptr and level.tiles[x + 1][y - 1]->movable and level.tiles[x + 1][y - 1]->getIsMoving()))
			{


				if (level.tiles[x][y] != nullptr and !level.tiles[x][y]->getIsMovingSideways())
				{
					if (level.tiles[x][y + 1] == nullptr) // falls down
					{
						if (player.playerPosTile.x == x and player.playerPosTile.y == y + 1 and level.tiles[x][y] != nullptr and level.tiles[x][y]->getIsMoving())
						{
							std::cout << "player dies !!!!!!!!!!!!!!!!!!!!! \n";
						}
						if (!(player.playerPosTile.x == x and player.playerPosTile.y == y + 1))
						{

							if (level.tiles[x][y]->fallDown())
							{

								if (player.playerPosTile.x == x and player.playerPosTile.y == y + 2 and level.tiles[x][y] != nullptr and level.tiles[x][y]->getIsMoving())
								{
									std::cout << "player dies !!!!!!!!!!!!!!!!!!!!! \n";
								}

								level.tiles[x][y]->changeIsMoving();

								level.tiles[x][y]->tilePosition.y = y + 1;


								level.tiles[x][y + 1] = level.tiles[x][y];
								level.tiles[x][y] = nullptr;

							}
						}
					}
					else if (level.tiles[x][y + 1] != nullptr and level.tiles[x][y + 1]->movable and !level.tiles[x][y + 1]->getIsMoving())
					{

						if (x >= 1 and level.tiles[x - 1][y] == nullptr and level.tiles[x - 1][y + 1] == nullptr) // left free
						{
							if (x >= 1 and level.tiles[x + 1][y] == nullptr and level.tiles[x + 1][y + 1] == nullptr) //right free
							{// both sides free
								if (!(player.playerPosTile.x == x + 1 and player.playerPosTile.y == y or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1) and !(player.playerPosTile.x == x - 1 and player.playerPosTile.y == y or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1))
								{// player not blocking left or right

									if (lastFellLeft) // falls right
									{
										if ((player.playerPosTile.x == x + 1 and player.playerPosTile.y == y or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getIsMoving())// player dies
										{// player on right
											std::cout << "player dies  right !!!!!!!!!!!!!!!!!!!!! \n";
										}
										if (level.tiles[x][y]->fallRight())
										{
											if ((player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 2 or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y] != nullptr and level.tiles[x][y]->getIsMoving()) // should player die
											{
												std::cout << "player dies right !!!!!!!!!!!!!!!!!!!!! \n";
											}
											level.tiles[x][y]->changeIsMoving();
											lastFellLeft = false;

											level.tiles[x][y]->tilePosition.y = y + 1;
											level.tiles[x][y]->tilePosition.x = x + 1;


											level.tiles[x + 1][y + 1] = level.tiles[x][y];
											level.tiles[x][y] = nullptr;
										}

									}
									else // falls left
									{
										if ((player.playerPosTile.x == x - 1 and player.playerPosTile.y == y or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getIsMoving())
										{ // player on left
											std::cout << "player dies  left !!!!!!!!!!!!!!!!!!!!! \n";
										}
										if (level.tiles[x][y]->fallLeft())
										{
											if ((player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 2 or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y] != nullptr and level.tiles[x][y]->getIsMoving())
											{
												std::cout << "player dies left !!!!!!!!!!!!!!!!!!!!! \n";
											}
											level.tiles[x][y]->changeIsMoving();
											lastFellLeft = true;

											level.tiles[x][y]->tilePosition.x = x - 1;
											level.tiles[x][y]->tilePosition.y = y + 1;


											level.tiles[x - 1][y + 1] = level.tiles[x][y];
											level.tiles[x][y] = nullptr;
										}
									}
								}
								else if (!(player.playerPosTile.x == x + 1 and player.playerPosTile.y == y or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1))
								{ // player is not on right
									if (level.tiles[x][y]->fallRight())
									{
										if ((player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 2 or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y] != nullptr and level.tiles[x][y]->getIsMoving()) // should player die
										{
											std::cout << "player dies right !!!!!!!!!!!!!!!!!!!!! \n";
										}
										level.tiles[x][y]->changeIsMoving();
										lastFellLeft = false;

										level.tiles[x][y]->tilePosition.x = x + 1;
										level.tiles[x][y]->tilePosition.y = y + 1;

										level.tiles[x + 1][y + 1] = level.tiles[x][y];
										level.tiles[x][y] = nullptr;
									}
								}
								else if (!(player.playerPosTile.x == x - 1 and player.playerPosTile.y == y or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1)) // player not blocking left
								{
									if ((player.playerPosTile.x == x - 1 and player.playerPosTile.y == y or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getIsMoving())
									{ // player on left
										std::cout << "player dies  left !!!!!!!!!!!!!!!!!!!!! \n";
									}
									if (level.tiles[x][y]->fallLeft())
									{
										if ((player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 2 or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y] != nullptr and level.tiles[x][y]->getIsMoving())
										{
											std::cout << "player dies left !!!!!!!!!!!!!!!!!!!!! \n";
										}
										level.tiles[x][y]->changeIsMoving();
										lastFellLeft = true;


										level.tiles[x][y]->tilePosition.x = x - 1;
										level.tiles[x][y]->tilePosition.y = y + 1;

										level.tiles[x - 1][y + 1] = level.tiles[x][y];
										level.tiles[x][y] = nullptr;
									}
								}
							}
							else if (!(player.playerPosTile.x == x - 1 and player.playerPosTile.y == y or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1)) // player not blocking left
							{
								if (level.tiles[x][y]->fallLeft())
								{
									if ((player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 2 or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y] != nullptr and level.tiles[x][y]->getIsMoving())
									{
										std::cout << "player dies left !!!!!!!!!!!!!!!!!!!!! \n";
									}
									level.tiles[x][y]->changeIsMoving();
									lastFellLeft = true;
									level.tiles[x][y]->tilePosition.x = x - 1;
									level.tiles[x][y]->tilePosition.y = y + 1;

									level.tiles[x - 1][y + 1] = level.tiles[x][y];
									level.tiles[x][y] = nullptr;
								}
							}
							else if (level.tiles[x][y]->getIsMoving())
								std::cout << "player dies  left !!!!!!!!!!!!!!!!!!!!! \n";
						}
						else if (x < level.mapSizeX - 1 and y < level.mapSizeY - 1 and level.tiles[x + 1][y] == nullptr and level.tiles[x + 1][y + 1] == nullptr)
						{//only right free
							if ((player.playerPosTile.x == x + 1 and player.playerPosTile.y == y or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getIsMoving())// gracz umiera
							{// player on right
								std::cout << "player dies  right !!!!!!!!!!!!!!!!!!!!! \n";
							}
							if (!(player.playerPosTile.x == x + 1 and player.playerPosTile.y == y or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1))
							{
								if (level.tiles[x][y]->fallRight())
								{
									if ((player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 2 or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y] != nullptr and level.tiles[x][y]->getIsMoving()) // should player die
									{
										std::cout << "player dies right !!!!!!!!!!!!!!!!!!!!! \n";
									}
									level.tiles[x][y]->changeIsMoving();
									lastFellLeft = false;

									level.tiles[x][y]->tilePosition.x = x + 1;
									level.tiles[x][y]->tilePosition.y = y + 1;

									level.tiles[x + 1][y + 1] = level.tiles[x][y];
									level.tiles[x][y] = nullptr;
								}
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
	findFallable();
	this->pollEvents();
	playerOnGameTile();
	this->player.update(canMoveLeft(), canMoveRight(), canMoveDown(), canMoveUp());
	tryMoveRockSideways();
	tryViewMove();
	moveView();
	keyboardInputs();

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
