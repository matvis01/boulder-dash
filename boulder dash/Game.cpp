#include "Game.h"

void Game::initVariables()
{
	this->viewIsMoving = false;
	whichMenu = GameState::menuWithContinue;

	for (int i = 0; i < 4; i++)
	{
		viewMoveDirection[i] = false;
	}
}

void Game::initWindow()
{
	this->videoMode = VideoMode(1280, 960);
	this->window = new RenderWindow(videoMode, "boulder dash", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(144);
}

void Game::setupMenus()
{
	menus.push_back(new Menu{ window,"NEW GAME","QUIT"});				// manu no continue
	menus.push_back(new Menu{ window,"CONTINUE", "NEW GAME","QUIT" });	// menu with continue
	menus.push_back(new Menu{ window,"CONTINUE","RESTART","MENU" });	//paused
	menus.push_back(new Menu{ window,"NEXT LEVEL","RESTART","MENU" });	// between levles
	menus.push_back(new Menu{ window,"RESTART","MENU" });				//death screen
	menus.push_back(new Menu{ window,"RESTART","MENU" });				//game finished
}

void Game::chooseFirstScreen()
{
	ifstream inputfile("saves\\save.txt");
	string line;

	getline(inputfile, line);
	istringstream(line) >> level.currentLevel;

	if (level.currentLevel == 0)
	{
		whichMenu = GameState::menuNoContinue;
	}
	else
		whichMenu = GameState::menuWithContinue;
}

void Game::canPushtoTrue()
{
	while (seconds(0.5) > clock.getElapsedTime())
	{
		waiting = true;
	}
	waiting = false;
	canPush = true;
}

void Game::CantPushAfterStop()
{
	if (player.playerPosTile.x < level.mapSizeX - 1 and player.playerPosTile.x > 0) // cant go outside of map
	{
		if (level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y] != nullptr and player.playerPosTile.x < level.mapSizeX - 2 and this->level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y]->getName() == Name::rock and this->level.tiles[player.playerPosTile.x + 2][player.playerPosTile.y] == nullptr and this->level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y + 1] != nullptr)
		{// single rock on right
		}
		else if (level.tiles[player.playerPosTile.x - 1][player.playerPosTile.y] != nullptr and player.playerPosTile.x >= 2 and this->level.tiles[player.playerPosTile.x - 1][player.playerPosTile.y]->getName() == Name::rock and this->level.tiles[player.playerPosTile.x - 2][player.playerPosTile.y] == nullptr and this->level.tiles[player.playerPosTile.x - 1][player.playerPosTile.y + 1] != nullptr)
		{// single rock on left
		}
		else if (level.tiles[player.playerPosTile.x][player.playerPosTile.y]!=nullptr)
		{// player pushing a rock
		}
		else
		{
			canPush = false;
		}
	}
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
				{
					if (canPush)
					{
						return true;
					}
					else if (!waiting)
					{
						clock.restart();
						threadToTrue.launch();
					}
				}
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
				{
					if (canPush)
					{
						return true;
					}
					else if (!waiting)
					{
						clock.restart();
						threadToTrue.launch();
					}
				}
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
	if (player.playerPosTile.y < level.mapSizeY-2) // cant go outside of map
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

void Game::initViews()
{
	this->view.setSize(1280.f, 960.f);
	this->view.setCenter(1280 / 2.f, 960 / 2.f - 80);

	this->hudView.setSize(1280.f, 960.f);
	this->hudView.setCenter(1280 / 2.f, 960 / 2.f);
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
	if (this->player.getPlayerPos().y > 320.f and this->player.getPlayerPos().y <  level.mapSizeY*80.f ) // dodac konce poziomu (and pos<costam.f)
	{
		if (this->player.getPlayerPos().y - 3 * 80.f >= view.getCenter().y)
		{
			viewNextSpoty = view.getCenter().y + 320.F;

			viewMoveDirection[DOWN] = true;
			viewIsMoving = true;
		}
		if (this->player.getPlayerPos().y + 3 * 80.f <= view.getCenter().y)
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
	initWindow();
	this->initViews();
	setupMenus();
	chooseFirstScreen();

	hud.setDiamondNumbers(level.diamondsCollected, level.diamondsRequired);
	player.setPlayerPos(level.playerStartingPos);
	hud.setDiamondNumbers(level.diamondsCollected, level.diamondsRequired);
	hud.updateDiamondAmount();
}

const bool Game::running() const
{
	return this->window->isOpen();
}

Game::~Game()
{
	
	for (int i = 0; i < menus.size(); i++)
	{
		delete this->menus[i];
	}
	delete this->window;
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		if (sfmlEvent.type == Event::Closed) this->window->close();

		if (sfmlEvent.type == Event::KeyPressed)
		{
			if (whichMenu == GameState::mainGame)
			{
				if (this->sfmlEvent.key.code == Keyboard::Escape)
					whichMenu = GameState::paused;
				if (this->sfmlEvent.key.code == Keyboard::R)
				{
					player.isMoving = false;
					viewIsMoving = false;
					loadCurrentLevel();
				}
			}
			else
			{
				if (this->sfmlEvent.key.code == Keyboard::Down or this->sfmlEvent.key.code == Keyboard::S)
					menus[whichMenu]->MoveDown();
				if (this->sfmlEvent.key.code == Keyboard::Up or this->sfmlEvent.key.code == Keyboard::W)
					menus[whichMenu]->MoveUp();

				if (this->sfmlEvent.key.code == Keyboard::Enter or this->sfmlEvent.key.code == Keyboard::Space)
				{
					if (whichMenu == GameState::menuNoContinue)
					{
						if (menus[whichMenu]->selectedButton == 0)
						{
							level.currentLevel = 0;
							loadCurrentLevel();
							whichMenu = GameState::mainGame;
						}
						else
							this->window->close();
					}
					if (whichMenu == GameState::menuWithContinue)
					{
							if (menus[whichMenu]->selectedButton == 0)
							{
								whichMenu = GameState::mainGame;
								loadCurrentLevel();
							}
							else if (menus[whichMenu]->selectedButton == 1)
							{
								whichMenu = GameState::mainGame;
								level.currentLevel = 0;

								ofstream outputFile("saves\\save.txt");
								if (outputFile.is_open())
								{
									outputFile << level.currentLevel;
									outputFile.close();
								}
								loadCurrentLevel();
							}
							else
								this->window->close();
					}
					if (whichMenu == GameState::paused)
					{
							if (menus[whichMenu]->selectedButton == 0)
							{
								whichMenu = GameState::mainGame;
							}
							else if (menus[whichMenu]->selectedButton == 1)
							{

								loadCurrentLevel();
								whichMenu = GameState::mainGame;
							}
							else
								whichMenu = GameState::menuWithContinue;
					}
					if (whichMenu == GameState::betweenLevels)
					{
							if (menus[whichMenu]->selectedButton == 0)
							{
								loadCurrentLevel();
								ofstream outputFile("saves\\save.txt");
								if (outputFile.is_open())
								{
									outputFile << level.currentLevel;
									outputFile.close();
								}
								whichMenu = GameState::mainGame;
							}
							else if (menus[whichMenu]->selectedButton == 1)
							{
								level.currentLevel--;
								loadCurrentLevel();
								whichMenu = GameState::mainGame;
							}
							else
								whichMenu = GameState::menuWithContinue;
					}
					if (whichMenu == GameState::deathScreen)
					{
							if (menus[whichMenu]->selectedButton == 0)
							{
								loadCurrentLevel();
								whichMenu = GameState::mainGame;
							}
							else
								whichMenu = GameState::menuWithContinue;
					}
					if (whichMenu == GameState::gameFinished)
					{
						if (menus[whichMenu]->selectedButton == 0)
						{
							loadCurrentLevel();
							whichMenu = GameState::mainGame;
						}
						else
						{
							level.currentLevel = 0;
							ofstream outputFile("saves\\save.txt");
							if (outputFile.is_open())
							{
								outputFile << level.currentLevel;
								outputFile.close();
							}
							whichMenu = GameState::menuNoContinue;
						}
					}
				}
			}
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
			hud.diamondsCollected += 1;
			hud.updateDiamondAmount();
			this->level.tiles[player.playerPosTile.x][player.playerPosTile.y] = nullptr;
		}
		else if (level.tiles[player.playerPosTile.x][player.playerPosTile.y]->getName() == Name::endlvl and level.diamondsCollected >= level.diamondsRequired)
		{// on EndLvl tile and collected enough diamonds
			if (level.currentLevel + 1 < level.howManyLevels)
			{// change to next level
				if (!player.isMoving)
				{
					level.currentLevel += 1;
					whichMenu = GameState::betweenLevels;
				}
			}
			else
			{
				std::cout << "game finished" << std::endl;
				whichMenu = GameState::gameFinished;
			}

		}
	}
}

void Game::loadCurrentLevel()
{
	player.isMoving = false;
	viewIsMoving = false;
	level.clearLevel();
	level.setupLevel();
	player.setPlayerPos(level.playerStartingPos);
	view.setCenter(1280 / 2.f, 960 / 2.f - 80);
	hud.resetHearts();
	hud.setDiamondNumbers(level.diamondsCollected, level.diamondsRequired);
	hud.updateDiamondAmount();
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
					clock.restart();
					//threadToFalse.launch();
					canPush = true;
					level.tiles[player.playerPosTile.x][player.playerPosTile.y]->tilePosition.x -= 1;
					level.tiles[player.playerPosTile.x - 1][player.playerPosTile.y] = level.tiles[player.playerPosTile.x][player.playerPosTile.y];
					level.tiles[player.playerPosTile.x][player.playerPosTile.y] = nullptr;
				}
			}
			else//player moves right
			{
				if (level.tiles[player.playerPosTile.x][player.playerPosTile.y]->moveSideways(false, player.getPlayerSpeed()))
				{
					clock.restart();
					/*threadToFalse.launch();*/
					canPush = true;
					level.tiles[player.playerPosTile.x][player.playerPosTile.y]->tilePosition.x += 1;
					level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y] = level.tiles[player.playerPosTile.x][player.playerPosTile.y];
					level.tiles[player.playerPosTile.x][player.playerPosTile.y] = nullptr;
				}
			}
		}
	}
}

void Game::playerHit(int x,int y)
{
	player.playHitSound();

	if (hud.heartsLeft > 1)
	{
		hud.removeHeart();
		hud.heartsLeft--;

		if (level.tiles[x][y] != nullptr)
		{
			level.tiles[x][y] = nullptr;
		}
	}
	else
		whichMenu = GameState::deathScreen;
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
			if (level.tiles[x][y] != nullptr and !level.tiles[x][y]->getIsMovingSideways())
			{
				if (level.tiles[x][y + 1] == nullptr) // falls down
				{	
					if (!(player.playerPosTile.x == x and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getName() == Name::rock)
					{
						if (level.tiles[x][y]->fallDown())
						{
							if (player.playerPosTile.x == x and player.playerPosTile.y == y + 2 and level.tiles[x][y]->getIsMoving() and level.tiles[x][y]->getName() == Name::rock)
							{
								std::cout << "player dies 2!!!!!!!!!!!!!!!!!!!!! \n";
								playerHit(x, y);
							}
							else
							{
								level.tiles[x][y]->changeIsMoving();
								level.tiles[x][y]->tilePosition.y = y + 1;

								level.tiles[x][y + 1] = level.tiles[x][y];
								level.tiles[x][y] = nullptr;
								level.tiles[x][y + 1]->setSpritePos({ x * 80.f + 40.f, (y + 1) * 80.f + 40.f });
							}
						}
					}
					else if (player.playerPosTile.x == x and player.playerPosTile.y == y + 1 and level.tiles[x][y]->getName() == Name::rock and level.tiles[x][y]->getIsMoving())
					{
						std::cout << "player dies 1!!!!!!!!!!!!!!!!!!!!! \n";
						playerHit(x, y);
					}
					else if (level.tiles[x][y] != nullptr and level.tiles[x][y]->getName() == Name::diamond)
					{//diamond can fall when a player is under it

						if (!(y >= 1 and level.tiles[x][y - 1] != nullptr and level.tiles[x][y - 1]->getName() == Name::rock))
						{// diamond can't fall if there is a rock above it
							if (level.tiles[x][y]->fallDown())
							{
								level.tiles[x][y]->changeIsMoving();
								level.tiles[x][y]->tilePosition.y = y + 1;
								level.tiles[x][y + 1] = level.tiles[x][y];
								level.tiles[x][y] = nullptr;
								level.tiles[x][y + 1]->setSpritePos({ x * 80.f + 40.f, (y + 1) * 80.f + 40.f });
							}
						}
					}
				}
				else if (level.tiles[x][y + 1] != nullptr and level.tiles[x][y + 1]->movable and !level.tiles[x][y + 1]->getIsMoving())
				{
					if (!(y >= 1 and level.tiles[x][y - 1] != nullptr and level.tiles[x][y - 1]->movable and level.tiles[x][y - 1]->getIsMoving()) and !(y >= 1 and x >= 1 and level.tiles[x - 1][y - 1] != nullptr and level.tiles[x - 1][y - 1]->movable and level.tiles[x - 1][y - 1]->getIsMoving()) and !(y >= 1 and x < level.mapSizeX - 2 and level.tiles[x + 1][y - 1] != nullptr and level.tiles[x + 1][y - 1]->movable and level.tiles[x + 1][y - 1]->getIsMoving()))
					{
						if (x >= 1 and level.tiles[x - 1][y] == nullptr and level.tiles[x - 1][y + 1] == nullptr) // left free
						{
							if (x >= 1 and level.tiles[x + 1][y] == nullptr and level.tiles[x + 1][y + 1] == nullptr) //right free
							{// both sides free
								if (!(player.playerPosTile.x == x + 1 and player.playerPosTile.y == y or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1) and !(player.playerPosTile.x == x - 1 and player.playerPosTile.y == y or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1))
								{// player not blocking left or right

									if (lastFellLeft) // falls right
									{
										if ((player.playerPosTile.x == x + 1 and player.playerPosTile.y == y or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getIsMoving() and level.tiles[x][y]->getName() == Name::rock)// player dies
										{// player on right
											std::cout << "player dies  right 3!!!!!!!!!!!!!!!!!!!!! \n";
											playerHit(x, y);
										}
										else if (level.tiles[x][y]->fallRight())
										{
											if ((player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 2 or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y] != nullptr and level.tiles[x][y]->getIsMoving() and level.tiles[x][y]->getName() == Name::rock) // should player die
											{
												std::cout << "player dies right 4!!!!!!!!!!!!!!!!!!!!! \n";
												playerHit(x, y);
											}
											else
											{
												level.tiles[x][y]->changeIsMoving();
												lastFellLeft = false;
												level.tiles[x][y]->tilePosition.y = y + 1;
												level.tiles[x][y]->tilePosition.x = x + 1;
												level.tiles[x + 1][y + 1] = level.tiles[x][y];
												level.tiles[x][y] = nullptr;
												level.tiles[x + 1][y + 1]->setSpritePos({ (x + 1) * 80.f + 40.f, (y + 1) * 80.f + 40.f });
											}
										}

									}
									else // falls left
									{
										if ((player.playerPosTile.x == x - 1 and player.playerPosTile.y == y or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getIsMoving() and level.tiles[x][y]->getName() == Name::rock)
										{ // player on left
											std::cout << "player dies  left !!!!!!!!!!!!!!!!!!!!! \n";
											playerHit(x, y);
										}
										else if (level.tiles[x][y]->fallLeft())
										{
											if ((player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 2 or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getIsMoving() and level.tiles[x][y]->getName() == Name::rock)
											{
												std::cout << "player dies left !!!!!!!!!!!!!!!!!!!!! \n";
												playerHit(x, y);
											}
											else
											{
												level.tiles[x][y]->changeIsMoving();
												lastFellLeft = true;

												level.tiles[x][y]->tilePosition.x = x - 1;
												level.tiles[x][y]->tilePosition.y = y + 1;


												level.tiles[x - 1][y + 1] = level.tiles[x][y];
												level.tiles[x][y] = nullptr;
												level.tiles[x - 1][y + 1]->setSpritePos({ (x - 1) * 80.f + 40.f, (y + 1) * 80.f + 40.f });
											}
										}
									}
								}
								else if (!(player.playerPosTile.x == x + 1 and player.playerPosTile.y == y or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1))
								{ // player is not on right
									if (level.tiles[x][y]->fallRight())
									{
										if ((player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 2 or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getName() == Name::rock and level.tiles[x][y]->getIsMoving()) // should player die
										{
											std::cout << "player dies right !!!!!!!!!!!!!!!!!!!!! \n";
											playerHit(x, y);
										}
										else
										{
											level.tiles[x][y]->changeIsMoving();
											lastFellLeft = false;

											level.tiles[x][y]->tilePosition.x = x + 1;
											level.tiles[x][y]->tilePosition.y = y + 1;

											level.tiles[x + 1][y + 1] = level.tiles[x][y];
											level.tiles[x][y] = nullptr;
											level.tiles[x + 1][y + 1]->setSpritePos({ (x + 1) * 80.f + 40.f, (y + 1) * 80.f + 40.f });
										}
									}
								}
								else if (!(player.playerPosTile.x == x - 1 and player.playerPosTile.y == y or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1)) // player not blocking left
								{
									if ((player.playerPosTile.x == x - 1 and player.playerPosTile.y == y or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getIsMoving() and level.tiles[x][y]->getName() == Name::rock)
									{ // player on left
										std::cout << "player dies  left !!!!!!!!!!!!!!!!!!!!! \n";
										playerHit(x, y);
									}
									else if (level.tiles[x][y]->fallLeft())
									{
										if ((player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 2 or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getName() == Name::rock and level.tiles[x][y]->getIsMoving())
										{
											std::cout << "player dies left !!!!!!!!!!!!!!!!!!!!! \n";
											playerHit(x, y);
										}
										else
										{
											level.tiles[x][y]->changeIsMoving();
											lastFellLeft = true;

											level.tiles[x][y]->tilePosition.x = x - 1;
											level.tiles[x][y]->tilePosition.y = y + 1;

											level.tiles[x - 1][y + 1] = level.tiles[x][y];
											level.tiles[x][y] = nullptr;
											level.tiles[x - 1][y + 1]->setSpritePos({ (x - 1) * 80.f + 40.f, (y + 1) * 80.f + 40.f });
										}
									}
								}
							}
							else if (!(player.playerPosTile.x == x - 1 and player.playerPosTile.y == y or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1)) // player not blocking left
							{
								if (level.tiles[x][y]->fallLeft())
								{
									if ((player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 2 or player.playerPosTile.x == x - 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getName() == Name::rock and level.tiles[x][y]->getIsMoving())
									{
										std::cout << "player dies left !!!!!!!!!!!!!!!!!!!!! \n";
										playerHit(x, y);
									}
									else
									{
										level.tiles[x][y]->changeIsMoving();
										lastFellLeft = true;
										level.tiles[x][y]->tilePosition.x = x - 1;
										level.tiles[x][y]->tilePosition.y = y + 1;

										level.tiles[x - 1][y + 1] = level.tiles[x][y];
										level.tiles[x][y] = nullptr;
										level.tiles[x - 1][y + 1]->setSpritePos({ (x - 1) * 80.f + 40.f, (y + 1) * 80.f + 40.f });
									}
								}
							}
							else if (level.tiles[x][y]->getIsMoving() and level.tiles[x][y]->getName() == Name::rock)
							{
								std::cout << "player dies  left !!!!!!!!!!!!!!!!!!!!! \n";
								playerHit(x, y);
							}
						}
						else if (x < level.mapSizeX - 1 and y < level.mapSizeY - 1 and level.tiles[x + 1][y] == nullptr and level.tiles[x + 1][y + 1] == nullptr)
						{//only right free
							if ((player.playerPosTile.x == x + 1 and player.playerPosTile.y == y or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getIsMoving() and level.tiles[x][y]->getName() == Name::rock)// gracz umiera
							{// player on right
								std::cout << "player dies  right !!!!!!!!!!!!!!!!!!!!! \n";
								playerHit(x, y);
							}
							else if (!(player.playerPosTile.x == x + 1 and player.playerPosTile.y == y or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1))
							{
								if (level.tiles[x][y]->fallRight())
								{
									if ((player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 2 or player.playerPosTile.x == x + 1 and player.playerPosTile.y == y + 1) and level.tiles[x][y]->getName() == Name::rock and level.tiles[x][y]->getIsMoving()) // should player die
									{
										std::cout << "player dies right !!!!!!!!!!!!!!!!!!!!! \n";
										playerHit(x, y);
									}
									else
									{
										level.tiles[x][y]->changeIsMoving();
										lastFellLeft = false;

										level.tiles[x][y]->tilePosition.x = x + 1;
										level.tiles[x][y]->tilePosition.y = y + 1;

										level.tiles[x + 1][y + 1] = level.tiles[x][y];
										level.tiles[x][y] = nullptr;
										level.tiles[x + 1][y + 1]->setSpritePos({ (x + 1) * 80.f + 40.f, (y + 1) * 80.f + 40.f });
									}
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
	if (whichMenu == GameState::mainGame)
	{
		this->player.update(canMoveLeft(), canMoveRight(), canMoveDown(), canMoveUp());
		findFallable();
		
		playerOnGameTile();
		tryMoveRockSideways();
		tryViewMove();
		moveView();
		CantPushAfterStop();
	}
	this->pollEvents();
}

void Game::render()
{
		this->window->clear();
		// stuff to render

		if (whichMenu == GameState::mainGame)
		{
		this->window->setView(view);
		this->level.render(this->window);
		this->player.render(this->window);
		this->window->setView(hudView);
		this->hud.render(this->window);
		}
		else
		{
			menus[whichMenu]->render();
		}
		//
		this->window->display();
}
