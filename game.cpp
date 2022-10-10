#include "game.h"
#include "surface.h"
#include "GameObject.h"
using namespace std;

GameObject* player;

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		player->Init();
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


	//Sprite theSprite(new Surface("assets/ball.png"), 1);
	void Game::Tick(float deltaTime)
	{
		Draw(screen);
		player->Tick(deltaTime);
	}

	void Game::Draw(Surface* screen)
	{
		screen->Clear(0);
		player->Draw(screen);
	}

	
	void Game::KeyDown(int key) //NOTE: Do not forget the "Game::" prefix, otherwise functions don't works
	{
		printf("%i %i", key, SDL_SCANCODE_O);
		if (key == SDL_SCANCODE_O)
		{
			printf("you've pressed the O key \n");
		}
	}
	
};