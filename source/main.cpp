#include "Game.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include <SDL3/SDL.h>
#include <exception>
#include <iostream>

int main()
{
	Game game;

	try
	{
		game.Init();
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what();
		game.Release();
		return -1;
	}

	while (game.IsRunning())
	{
		TM.Update();
		std::cout << TM.GetDeltaTime() << std::endl;
		if (TM.ShouldUpdateGame()) {
			game.HandleEvents();
			game.Update();
			game.Render();
			TM.ResetDeltaTime();
		}
		
	}

	game.Release();

	return 0;
}