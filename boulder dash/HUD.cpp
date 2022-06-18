#include "HUD.h"

HUD::HUD()
{
	font.loadFromFile("fonts/ARCADE_I.ttf");
	diamondAmount.setFont(font);
	diamondAmount.setCharacterSize(80);
	diamondAmount.setString(toString(diamondsCollected) + "/" + toString(diamondsRequired));
	diamondAmount.setOrigin(-20, 5);

	blackBar.setSize(Vector2f(1280.f, 80.f));
	blackBar.setFillColor(Color::Black);

	textureRed.loadFromFile("assets\\heart.png");
	textureGray.loadFromFile("assets\\heartempty.png");
	sprites[0].setTexture(textureRed);
	sprites[1].setTexture(textureRed);
	sprites[2].setTexture(textureRed);

	sprites[2].setPosition(1100.f, 8.f);
	sprites[1].setPosition(1000.f, 8.f);
	sprites[0].setPosition(900.f, 8.f);
}

HUD::~HUD()
{
}

String HUD::toString(int num)
{
	char numstr[5];
	sprintf_s(numstr, "%i", num);
	return numstr;
}

void HUD::removeHeart()
{
	if (heartsLeft == 3)
	{
		sprites[0].setTexture(textureGray);
	}
	else if (heartsLeft == 2)
	{
		sprites[1].setTexture(textureGray);
	}
}

void HUD::resetHearts()
{
	heartsLeft = 3;
	sprites[0].setTexture(textureRed);
	sprites[1].setTexture(textureRed);
	sprites[2].setTexture(textureRed);
}

void HUD::updateDiamondAmount()
{
	diamondAmount.setString(toString(diamondsCollected) + "/" + toString(diamondsRequired));
}

void HUD::setDiamondNumbers(int collected,int required)
{
	this->diamondsCollected = collected;
	this->diamondsRequired = required;
}

void HUD::render(RenderTarget* target)
{
	target->draw(blackBar);
	target->draw(diamondAmount);
	target->draw(sprites[0]);
	target->draw(sprites[1]);
	target->draw(sprites[2]);
}
