#include "game.h"
#include "surface.h"
#include "Components.h"

using namespace std;

#define TILE_SIZE 32

Manager manager;
auto& newPlayer(manager.addObject());

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		newPlayer.addComponent<TransformComponent>(100, 100);
		newPlayer.addComponent<ShapeComponent>(t_rectangle);
		//newPlayer.getComponent<ShapeComponent>().pShape.radius = 16;

		//newPlayer.getComponent<ShapeComponent>().pShape.radius = 16;
		//newPlayer.getComponent<ShapeComponent>().pShape.transform = Vector2D(100, 100);
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
		newPlayer.getComponent<TransformComponent>().position = Vector2D(mousex, mousey);

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