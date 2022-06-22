#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <vector>
#include <string>

enum class Name { rock, wall, ground, diamond, endlvl };

enum MoveDirection { UP, DOWN, LEFT, RIGHT };

enum GameState { menuNoContinue, menuWithContinue, paused, betweenLevels, deathScreen, gameFinished, mainGame };

struct tilePos
{
	int x;
	int y;
};