#pragma once
#include "functions.h"
#include <iostream>
#include <string>


using namespace sf;

class HUD
{
	Font font;
	Text diamondAmount;
	RectangleShape blackBar;
	Sprite sprites[3];
	Texture textureRed, textureGray;
	
public:

	int heartsLeft = 3;
	int diamondsCollected = 0;
	int diamondsRequired = 1;

	HUD();
	~HUD();
	String toString(int);
	void removeHeart();
	void resetHearts();
	void updateDiamondAmount();
	void setDiamondNumbers(int,int);
	void render(RenderTarget* target);

};

