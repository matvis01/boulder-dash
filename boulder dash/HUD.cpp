#include "HUD.h"

HUD::HUD()
{
	if (!font.loadFromFile("fonts/ARCADE_I.ttf"))
		std::cout << ("could not load hud font");
	diamondAmount.setFont(font);
	diamondAmount.setCharacterSize(80);
	diamondAmount.setString(toString(diamondsCollected) + "/" + toString(diamondsRequired));
	diamondAmount.setOrigin(-20, 5);

	blackBar.setSize(Vector2f(1280.f, 80.f));
	blackBar.setFillColor(Color::Black);
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
}
