#include "game.h"
#include "surface.h"
#include "GameObject.h"
#include "Transform.h"

#include "RectCollider.h"
#include "Player.h"
#include "Tile.h"
#include "TileMap.h"
using namespace std;

#define TILE_SIZE 32


namespace Tmpl8
{
	Player* player;
	Map* tilemap;

	//const int tileCount = 5;
	
	//Tile* tiles [tileCount];

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		tilemap = new Map();
		player = new Player(vec2(TILE_SIZE * 4, TILE_SIZE * 4));
		player->setRadius(4);
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

		/**/
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (tilemap->getTile(i, j)->getReal())
				{
					if (tilemap->getTile(i, j)->GetRectCollider()->IsCircleColliding(player->GetCircleCollider()))
					{
						vec2 point = tilemap->getTile(i, j)->GetRectCollider()->GetPointOnRect(player->GetCircleCollider());
						point = tilemap->getTile(i, j)->GetRectCollider()->checkIfPointInRect(point);
						vec2 side = tilemap->getTile(i, j)->GetRectCollider()->FindSideDirection(point);
						player->ChangeTrajectory(side, point);
					}
					tilemap->getTile(i, j)->GetRectCollider()->updatePrevPointOnRect();
				}
				
			}
		}
		/**/
	}

	void Game::Draw(Surface* screen)
	{
		screen->Clear(0);
		player->Draw(screen);
		tilemap->DrawMap(screen);

		//TESTING PURPOSES
		int x1;
		int y1;
		x1 = 44.604416;
		y1 = 128;
		screen->ApproximateCircle(x1, y1, 16, 255 * 1 * 1);

		x1 = 60.700455;
		y1 = 128;
		screen->ApproximateCircle(x1, y1, 8, 255 * 255 * 255);

		x1 = 44.604416;
		y1 = 128;
		screen->ApproximateCircle(x1, y1, 8, 255 * 1 * 255);


	}

	
	void Game::KeyDown(int key) //NOTE: Do not forget the "Game::" prefix, otherwise functions don't works
	{
		player->Input(key);	
	}
	
};