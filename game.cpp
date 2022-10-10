#include "game.h"
#include "surface.h"
#include <cstdio> //printf

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------


	Sprite theSprite(new Surface("assets/ball.png"), 1);
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		theSprite.Draw(screen, 0, 0);
	}
};