#include "game.h"
#include "surface.h"
#include "GameObject.h"
#include "Transform.h"

#include "RectCollider.h"
#include "Player.h"
#include "Tile.h"
using namespace std;

#define TILE_SIZE 48


namespace Tmpl8
{
	Player* player;
	Tile* tiles [4];

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		player = new Player(vec2(TILE_SIZE * 4, TILE_SIZE * 4));
		player->setRadius(8);
		
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				tiles[i] = new Tile(vec2(0, TILE_SIZE));
				tiles[i]->setRect(TILE_SIZE, TILE_SIZE * 8);
			}
			if (i == 1)
			{
				tiles[i] = new Tile(vec2(TILE_SIZE, 0));
				tiles[i]->setRect(TILE_SIZE * 8, TILE_SIZE);
			}
			if (i == 2)
			{
				tiles[i] = new Tile(vec2(TILE_SIZE * 9, TILE_SIZE));
				tiles[i]->setRect(TILE_SIZE, TILE_SIZE * 8);
			}
			if (i == 3)
			{
				tiles[i] = new Tile(vec2(TILE_SIZE, TILE_SIZE * 9));
				tiles[i]->setRect(TILE_SIZE * 8, TILE_SIZE);
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
			tiles[i]->GetRectCollider()->Draw(screen);
		}
	}

	
	void Game::KeyDown(int key) //NOTE: Do not forget the "Game::" prefix, otherwise functions don't works
	{
		player->Input(key);	
	}
	
};