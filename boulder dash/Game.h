#pragma once

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "Player.h"
#include "GameTile.h"
#include "Level.h"


using namespace sf;


class Game
{
	VideoMode videoMode;
	RenderWindow* window;
	bool endGame;
	Event sfmlEvent;

	View view;
	bool viewIsMoving;
	float viewNextSpotx, viewNextSpoty;
	bool viewMoveDirection[4];

	Player player;
	Level level;

	bool canMoveLeft();
	bool canMoveRight();
	bool canMoveUp();
	bool canMoveDown();

	void initVariables();

	void initWindow();

	void initView();
	void tryViewMove();
	void moveView();

	void removeGround();


public:
	Game();
	~Game();

	const bool running() const;
	void pollEvents();

	void findRock();

	void update();
	void render();

};

