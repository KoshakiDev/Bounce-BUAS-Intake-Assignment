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
	Tile* tile1;
	Tile* tile2;


	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		player = new Player(vec2(400, 400));
		player->setRadius(32);
		tile1 = new Tile(vec2(500, 400));
		tile1->setRect(32, 32);
		tile2 = new Tile(vec2(200, 400));
		tile2->setRect(32, 32);
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
		tile1->Tick(deltaTime);
		tile2->Tick(deltaTime);
		if (tile1->GetRectCollider()->IsCircleColliding(player->GetCircleCollider()) || tile2->GetRectCollider()->IsCircleColliding(player->GetCircleCollider()))
		{
			vec2 velocity = player->GetVelocity();
			velocity = -velocity * 0.9;
			player->SetVelocity(velocity);
		}
			

	}

	void Game::Draw(Surface* screen)
	{
		screen->Clear(0);
		player->Draw(screen);
		tile1->Draw(screen);
		tile2->Draw(screen);
	}

	
	void Game::KeyDown(int key) //NOTE: Do not forget the "Game::" prefix, otherwise functions don't works
	{
		player->Input(key);	
	}
	
};