#pragma once
#include "functions.h"
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

using namespace sf;

class HUD
{
	Font font;
	Text diamondAmount;
	RectangleShape blackBar;


public:

	int diamondsCollected = 0;
	int diamondsRequired = 1;

	HUD();
	~HUD();
	String toString(int);
	void updateDiamondAmount();
	void setDiamondNumbers(int,int);
	void render(RenderTarget* target);

};

