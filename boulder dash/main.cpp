//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#include "Game.h"
#include "Game.h"

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	
	while (game.running())
	{
		game.update();
		game.render();
	}


	return 0;
}