#include "game.h"
#include "surface.h"
#include "Components.h"
#include "Objects.h"

using namespace std;

#define TILE_SIZE 32

Manager manager;

/*
The game does not have a "player". Instead, there are numerous components working together which form a "player".
I started out with a "player.cpp", but then throughout development, the component system worked so well, it made
the "player.cpp" redundant.
*/


Object& Player = manager.addObject();

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		//Creating the player
		Player.addComponent<TransformComponent>(100, 100);
		Player.addComponent<KinematicsComponent>(1, 1);
		Player.addComponent<ShapeComponent>(t_circle);
		Player.getComponent<ShapeComponent>().pShape->params["radius"] = 16;

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
	void Game::Tick(float delta)
	{
		manager.refresh();
		manager.Tick(delta);
		Draw(screen);
		//newPlayer.getComponent<TransformComponent>().position = Vector2D(mousex, mousey);

		/*
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (tilemap->getTile(i, j)->getReal())
				{
					if (tilemap->getTile(i, j)->GetRectCollider()->IsCircleColliding(player->GetCircleCollider()))
					{
						Vector2D point = tilemap->getTile(i, j)->GetRectCollider()->GetPointOnRect(player->GetCircleCollider());
						point = tilemap->getTile(i, j)->GetRectCollider()->checkIfPointInRect(point);
						Vector2D side = tilemap->getTile(i, j)->GetRectCollider()->FindSideDirection(point);
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
		manager.Draw(screen);
	}

	
	void Game::KeyDown(int key) //NOTE: Do not forget the "Game::" prefix, otherwise functions don't works
	{
		//player->Input(key);	
	}
	
};