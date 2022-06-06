#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <filesystem>
#include <sstream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"
#include "GameTile.h"
#include "Level.h"
#include "HUD.h"
#include "Menu.h"

using namespace sf;
using namespace std;

class Game
{
	RenderWindow* window;
	View view;
	View hudView;
	VideoMode videoMode;
	Event sfmlEvent;

	bool viewIsMoving;
	float viewNextSpotx, viewNextSpoty;
	bool viewMoveDirection[4];

	Player player;
	Level level;
	HUD hud;


	vector<Menu*> menus;
	void setupMenus();
	int whichMenu;
	void chooseFirstScreen();
	

	Clock clock;
	bool canPush = false;
	bool waiting = false;
	void canPushtoTrue();
	Thread threadToTrue{ &Game::canPushtoTrue,this };
	void CantPushAfterStop();

	bool canMoveLeft();
	bool canMoveRight();
	bool canMoveUp();
	bool canMoveDown();

	void initVariables();
	void initWindow();

	void initViews();
	void tryViewMove();
	void moveView();

	void playerOnGameTile();
	void loadCurrentLevel();

	void playerHit(int x, int y);
	void findFallable();
	bool lastFellLeft;
	void tryMoveRockSideways();

public:
	Game();
	~Game();


	void pollEvents();

	const bool running() const;
	void update();
	void render();

};

