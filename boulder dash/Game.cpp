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
			if (player.playerPosTile.x >= 2 and this->level.tiles[player.playerPosTile.x - 1][player.playerPosTile.y]->getName() == Name::rock and 
				this->level.tiles[player.playerPosTile.x - 2][player.playerPosTile.y] == nullptr and this->level.tiles[player.playerPosTile.x-1 ][player.playerPosTile.y+1] != nullptr)
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
				{
					return false;
				}
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
	if (this->player.getPlayerPos().y > 5*80.f and this->player.getPlayerPos().y < (level.mapSizeY - 5)*80.f)
	{
		if (!viewIsMoving and this->player.getPlayerPos().y - 4 * 80.f > view.getCenter().y)
		{
			viewNextSpoty = view.getCenter().y + 320.F;

			viewMoveDirection[DOWN] = true;
			viewIsMoving = true;
		}
		if (!viewIsMoving and this->player.getPlayerPos().y + 3 * 80.f <=view.getCenter().y)
		{
			viewNextSpoty = view.getCenter().y - 320.f;

			viewMoveDirection[UP] = true;
			viewIsMoving = true;
		}
	}
	if (this->player.getPlayerPos().x > 5 * 80.f and this->player.getPlayerPos().x < (level.mapSizeX - 5) * 80.f)
	{
		if (!viewIsMoving and this->player.getPlayerPos().x - 4 * 80.f >= view.getCenter().x)
		{
			viewNextSpotx = view.getCenter().x + 400.f;

			viewMoveDirection[RIGHT] = true;
			viewIsMoving = true;
		}
		if (!viewIsMoving and this->player.getPlayerPos().x + 4 * 80.f <= view.getCenter().x)
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
			sound.playGround();
			this->level.tiles[player.playerPosTile.x][player.playerPosTile.y] = nullptr;
		}
		else if (level.tiles[player.playerPosTile.x][player.playerPosTile.y]->getName() == Name::diamond)
		{
			sound.playDiamond();
			level.diamondsCollected += 1;
			hud.diamondsCollected += 1;
			hud.updateDiamondAmount();
			this->level.tiles[player.playerPosTile.x][player.playerPosTile.y] = nullptr;
			if (this->level.tiles[player.playerPosTile.x][player.playerPosTile.y - 1] != nullptr and this->level.tiles[player.playerPosTile.x][player.playerPosTile.y - 1]->getName() == Name::rock)
			{
				level.tiles[player.playerPosTile.x][player.playerPosTile.y - 1]->changeIsMoving();
			}
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
					canPush = true;
					level.tiles[player.playerPosTile.x][player.playerPosTile.y]->tilePosition.x += 1;
					level.tiles[player.playerPosTile.x + 1][player.playerPosTile.y] = level.tiles[player.playerPosTile.x][player.playerPosTile.y];
					level.tiles[player.playerPosTile.x][player.playerPosTile.y] = nullptr;
				}
			}
		}
	}
}

void Game::playerHit(int x, int y)
{
	if (hud.heartsLeft > 1)
	{
		sound.playHit();
		hud.removeHeart();
		hud.heartsLeft--;
		if (level.tiles[x][y] != nullptr)
		{
			level.tiles[x][y] = nullptr;
		}
	}
	else
	{
		sound.playdeath();
		whichMenu = GameState::deathScreen;
	}
}

void Game::findFallable()
{
	int px = player.playerPosTile.x;
	int py = player.playerPosTile.y;

	for (int v = 0; v < level.allFallable.size(); v++)
	{
		int y, x;
		x = this->level.allFallable[v]->tilePosition.x;
		y = this->level.allFallable[v]->tilePosition.y;

		auto& thisTile = level.tiles[x][y];
		auto& below = level.tiles[x][y + 1];
		auto& left = level.tiles[x - 1][y];
		auto& right = level.tiles[x + 1][y];
		auto& leftDown = level.tiles[x - 1][y + 1];
		auto& rightDown = level.tiles[x + 1][y + 1];

		if (thisTile != nullptr and !thisTile->getIsMovingSideways())
		{
			if (below == nullptr) // falls down
			{
				if (!(px == x and py == y + 1))
				{
					if (thisTile->fallDown())
					{
						if (px == x and py == y + 2 and thisTile->getIsMoving())
						{
							playerHit(x, y);
						}
						else
						{
							if (level.tiles[x][y + 2] != nullptr)
							{
								sound.playRockFall();
							}
							thisTile->changeIsMoving();
							thisTile->tilePosition.y = y + 1;
							below = thisTile;
							thisTile = nullptr;
							below->setSpritePos({ x * 80.f + 40.f, (y + 1) * 80.f + 40.f });
						}
					}
				}
				else if (px == x and py == y + 1 and thisTile->getIsMoving())
				{
					playerHit(x, y);
				}
			}
			else if (below != nullptr and below->movable and !below->getIsMoving())
			{// fallable on fallable
				if (!(y >= 1 and level.tiles[x][y - 1] != nullptr and level.tiles[x][y - 1]->movable and level.tiles[x][y - 1]->getIsMoving()) and !(y >= 1 and x >= 1 and level.tiles[x - 1][y - 1] != nullptr and level.tiles[x - 1][y - 1]->movable and level.tiles[x - 1][y - 1]->getIsMoving()) and !(y >= 1 and x < level.mapSizeX - 2 and level.tiles[x + 1][y - 1] != nullptr and level.tiles[x + 1][y - 1]->movable and level.tiles[x + 1][y - 1]->getIsMoving()))
				{//so it doest colide with falling next to it
					if (x >= 1 and left == nullptr and leftDown == nullptr) // left free
					{//left side free
						if (right == nullptr and rightDown == nullptr) //right free
						{// both sides free
							if (!(px == x + 1 and py == y or px == x + 1 and py == y + 1) and !(px == x - 1 and py == y or px == x - 1 and py == y + 1))
							{// player not blocking left or right
								if (lastFellLeft) // falls right
								{
									if ((px == x + 1 and py == y or px == x + 1 and py == y + 1) and thisTile->getIsMoving() and thisTile->getName() == Name::rock)// player dies
									{// player on right
										playerHit(x, y);
									}
									else if (thisTile->fallRight())
									{
										if ((px == x + 1 and py == y + 2 or px == x + 1 and py == y + 1) and thisTile != nullptr and thisTile->getIsMoving() and thisTile->getName() == Name::rock) // should player die
										{
											playerHit(x, y);
										}
										else
										{
											if (level.tiles[x][y + 2] != nullptr)
											{
												sound.playRockFall();
											}
											thisTile->changeIsMoving();
											lastFellLeft = false;
											thisTile->tilePosition.y = y + 1;
											thisTile->tilePosition.x = x + 1;
											rightDown = thisTile;
											thisTile = nullptr;
											rightDown->setSpritePos({ (x + 1) * 80.f + 40.f, (y + 1) * 80.f + 40.f });
										}
									}

								}
								else // falls left
								{
									if ((px == x - 1 and py == y or px == x - 1 and py == y + 1) and thisTile->getIsMoving() and thisTile->getName() == Name::rock)
									{ // player on left
										playerHit(x, y);
									}
									else if (thisTile->fallLeft())
									{
										if ((px == x - 1 and py == y + 2 or px == x - 1 and py == y + 1) and thisTile->getIsMoving() and thisTile->getName() == Name::rock)
										{
											playerHit(x, y);
										}
										else
										{
											if (level.tiles[x][y + 2] != nullptr)
											{
												sound.playRockFall();
											}
											thisTile->changeIsMoving();
											lastFellLeft = true;

											thisTile->tilePosition.x = x - 1;
											thisTile->tilePosition.y = y + 1;
											leftDown = thisTile;
											thisTile = nullptr;
											leftDown->setSpritePos({ (x - 1) * 80.f + 40.f, (y + 1) * 80.f + 40.f });
										}
									}
								}
							}
							else if (!(px == x + 1 and py == y or px == x + 1 and py == y + 1))
							{ // player is not on right
								if (thisTile->fallRight())
								{
									if ((px == x + 1 and py == y + 2 or px == x + 1 and py == y + 1) and thisTile->getName() == Name::rock and thisTile->getIsMoving()) // should player die
									{
										playerHit(x, y);
									}
									else
									{
										if (level.tiles[x][y + 2] != nullptr)
										{
											sound.playRockFall();
										}
										thisTile->changeIsMoving();
										lastFellLeft = false;
										thisTile->tilePosition.x = x + 1;
										thisTile->tilePosition.y = y + 1;
										rightDown = thisTile;
										thisTile = nullptr;
										rightDown->setSpritePos({ (x + 1) * 80.f + 40.f, (y + 1) * 80.f + 40.f });
									}
								}
							}
							else if (!(px == x - 1 and py == y or px == x - 1 and py == y + 1)) // player not blocking left
							{//player is not on the left
								if ((px == x - 1 and py == y or px == x - 1 and py == y + 1) and thisTile->getIsMoving() and thisTile->getName() == Name::rock)
								{ // player on left
									playerHit(x, y);
								}
								else if (thisTile->fallLeft())
								{
									if ((px == x - 1 and py == y + 2 or px == x - 1 and py == y + 1) and thisTile->getName() == Name::rock and thisTile->getIsMoving())
									{
										playerHit(x, y);
									}
									else
									{
										if (level.tiles[x][y + 2] != nullptr)
										{
											sound.playRockFall();
										}
										thisTile->changeIsMoving();
										lastFellLeft = true;
										thisTile->tilePosition.x = x - 1;
										thisTile->tilePosition.y = y + 1;
										leftDown = thisTile;
										thisTile = nullptr;
										leftDown->setSpritePos({ (x - 1) * 80.f + 40.f, (y + 1) * 80.f + 40.f });
									}
								}
							}
						}
						else if (!(px == x - 1 and py == y or px == x - 1 and py == y + 1))
						{// player not blocking left
							if (thisTile->fallLeft())
							{
								if ((px == x - 1 and py == y + 2 or px == x - 1 and py == y + 1) and thisTile->getName() == Name::rock and thisTile->getIsMoving())
								{
									playerHit(x, y);
								}
								else
								{
									if (level.tiles[x][y + 2] != nullptr)
									{
										sound.playRockFall();
									}
									thisTile->changeIsMoving();
									lastFellLeft = true;
									thisTile->tilePosition.x = x - 1;
									thisTile->tilePosition.y = y + 1;
									leftDown = thisTile;
									thisTile = nullptr;
									leftDown->setSpritePos({ (x - 1) * 80.f + 40.f, (y + 1) * 80.f + 40.f });
								}
							}
						}
						else if (thisTile->getIsMoving() and thisTile->getName() == Name::rock)
						{
							playerHit(x, y);
						}
					}
					else if (x < level.mapSizeX - 1 and y < level.mapSizeY - 1 and right == nullptr and rightDown == nullptr)
					{//only right free
						if ((px == x + 1 and py == y or px == x + 1 and py == y + 1) and thisTile->getIsMoving() and thisTile->getName() == Name::rock)
						{// player on right
							playerHit(x, y);
						}
						else if (!(px == x + 1 and py == y or px == x + 1 and py == y + 1))
						{// player not on right
							if (thisTile->fallRight())
							{
								if ((px == x + 1 and py == y + 2 or px == x + 1 and py == y + 1) and thisTile->getName() == Name::rock and thisTile->getIsMoving())
								{
									playerHit(x, y);
								}
								else
								{
									if (level.tiles[x][y + 2] != nullptr)
									{
										sound.playRockFall();
									}
									thisTile->changeIsMoving();
									lastFellLeft = false;
									thisTile->tilePosition.x = x + 1;
									thisTile->tilePosition.y = y + 1;

									rightDown = thisTile;
									thisTile = nullptr;
									rightDown->setSpritePos({ (x + 1) * 80.f + 40.f, (y + 1) * 80.f + 40.f });
								}
							}
						}
					}
				}
			}
		}
	}
}

void Game::updateEnemies()
{
	bool b[4];
	for (int i = 0; i < level.enemies.size(); i++)
	{
		if (level.enemies[i] != nullptr)
		{
			b[LEFT] = level.enemyCanGoLeft(i);
			b[UP] = level.enemyCanGoUp(i);
			b[DOWN] = level.enemyCanGoDown(i);
			b[RIGHT] = level.enemyCanGoRight(i);
			level.enemies[i]->update(b);

			if (level.enemies[i]->LastPosTile.x == player.playerPosTile.x and level.enemies[i]->LastPosTile.y == player.playerPosTile.y)
			{
				sound.playSpiderAttack();
				level.enemies[i] = nullptr;
				playerHit(player.playerPosTile.x, player.playerPosTile.y);
			}


			for (int j = 0; j < level.allFallable.size(); j++)
			{
				if (level.allFallable[j] != nullptr and level.tiles[level.allFallable[j]->tilePosition.x][level.allFallable[j]->tilePosition.y] != nullptr and level.enemies[i] != nullptr)
				{
					if (level.allFallable[j]->tilePosition.x == level.enemies[i]->PosTile.x and level.allFallable[j]->tilePosition.y == level.enemies[i]->PosTile.y)
					{
						sound.playSpiderDie();
						level.enemies[i] = nullptr;
					}
					else if (level.allFallable[j]->tilePosition.x == level.enemies[i]->LastPosTile.x and level.allFallable[j]->tilePosition.y == level.enemies[i]->LastPosTile.y)
					{
						sound.playSpiderDie();
						level.enemies[i] = nullptr;
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
		
		findFallable();
		this->player.update(canMoveLeft(), canMoveRight(), canMoveDown(), canMoveUp());
		playerOnGameTile();
		tryMoveRockSideways();
		tryViewMove();
		moveView();
		CantPushAfterStop();
		updateEnemies();
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
		this->level.renderEnemies(this->window);
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
