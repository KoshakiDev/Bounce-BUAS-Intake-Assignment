#include "game.h"
#include "surface.h"
#include "GameObject.h"
#include "Transform.h"

#include "RectCollider.h"
#include "Player.h"
#include "Tile.h"
using namespace std;


namespace Tmpl8
{
	Player* player;
	Tile* tiles [4];

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		player = new Player(vec2(120, 120));
		player->setRadius(8);
		
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				tiles[i] = new Tile(vec2(32, 32));
				tiles[i]->setRect(32, 32 * 8);
			}
			if (i == 1)
			{
				tiles[i] = new Tile(vec2(32, 32));
				tiles[i]->setRect(32 * 8, 32);
			}
			if (i == 2)
			{
				tiles[i] = new Tile(vec2(32 * 8, 32));
				tiles[i]->setRect(32, 32 * 8);
			}
			if (i == 3)
			{
				tiles[i] = new Tile(vec2(32, 32 * 8));
				tiles[i]->setRect(32 * 8, 32);
			}
		}
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
		for (int i = 0; i < 4; i++)
		{
			if (tiles[i]->GetRectCollider()->IsCircleColliding(player->GetCircleCollider()))
			{
				player->ChangeTrajectory(tiles[i]->GetRectCollider()->GetDistanceFromCircle(player->GetCircleCollider()));
			}
		}
	}

	void Game::Draw(Surface* screen)
	{
		screen->Clear(0);
		player->Draw(screen);
		for (int i = 0; i < 4; i++)
		{
			tiles[i]->Draw(screen);
		}
	}

	
	void Game::KeyDown(int key) //NOTE: Do not forget the "Game::" prefix, otherwise functions don't works
	{
		player->Input(key);	
	}
	
};