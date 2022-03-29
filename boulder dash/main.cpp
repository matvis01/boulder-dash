#include "Game.h"
#include "Player.h"

int main()
{
	Game game;

	while (game.running())
	{
		game.update();
		game.render();
	}

	return 0;
}