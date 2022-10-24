#include "game.h"
#include "surface.h"
#include "Components.h"

using namespace std;

#define TILE_SIZE 32

Manager manager;

/*
The game does not have a "player". Instead, there are numerous components working together which form a "player".
I started out with a "player.cpp", but then throughout development, the component system worked so well, it made
the "player.cpp" redundant.
*/


int rgb(int red, int green, int blue)
{
	return (0 << ALPHA) + (red << RED) + (green << GREEN) + (blue << BLUE);
}


Pixel moldy_white = rgb(240, 246, 240);
Pixel moldy_black = rgb(34, 35, 35);

// debug colors
Pixel red = rgb(255, 0, 0);
Pixel yellow = rgb(255, 255, 0);
Pixel green = rgb(0, 255, 0);
Pixel blue = rgb(0, 0, 255);

Object& player = manager.addObject();
Map* tilemap;

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));


namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		//Creating the player

		player.addComponent<TransformComponent>(500, 500);
		player.addComponent<KinematicsComponent>(0.1, 0.5);
		player.addComponent<ShapeComponent>(t_circle);
		player.getComponent<ShapeComponent>().pShape->params["radius"] = 16;
		player.getComponent<ShapeComponent>().pShape->color = moldy_black;

		tilemap = new Map(32);
		tilemap->LoadMap("default.map", 25, 20, moldy_black);
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


	void Game::Tick(float delta)
	{
		manager.refresh();
		manager.Tick(delta);
		
		/*
		Well, the trick there is to not let the circle intersect with the box in the first place. 
		When you move you check if there's something at your new position, and if not, you move. 
		Not the other way around where you move and then check : )
		*/

		for (auto& t : tiles)
		{
			Vector2D penetration_normal = Vector2D(-1, -1);
			float penetration_depth = 0;

			if (Collision::Check(
				player.getComponent<ShapeComponent>().pShape, 
				t->getComponent<ShapeComponent>().pShape, 
				penetration_normal,
				penetration_depth)
			)
			{
				/*
				// Make the ball slide on the surface
				Vector2D velocity_length = player.getComponent<KinematicsComponent>().velocity.length();
				Vector2D velocity_normalized = player.getComponent<KinematicsComponent>().velocity.normalized();
				float dot_product = velocity_normalized.dot(penetration_normal);
				Vector2D undesired_motion = penetration_normal * dot_product;
				Vector2D desired_motion = velocity_normalized - undesired_motion;
				player.getComponent<KinematicsComponent>().velocity = desired_motion * velocity_length;
				/**/

				// This changes the velocity trajectory
				if (penetration_normal.x != 0)
				{
					player.getComponent<KinematicsComponent>().velocity.x *= -1 * abs(penetration_normal.x);
				}
				else if (penetration_normal.y != 0)
				{
					player.getComponent<KinematicsComponent>().velocity.y *= -1 * abs(penetration_normal.y);
				}

				// Remove penetration (penetration epsilon added to handle infinitely small penetration):
				player.getComponent<TransformComponent>().Translate(penetration_normal * (penetration_depth + 0.0001f));
			}
		}
		Draw(screen);
	}

	void Game::Draw(Surface* screen)
	{
		screen->Clear(moldy_white);
		manager.Draw(screen);
	}

	void Game::MouseUp(int button)
	{
		manager.MouseUp(button);
	}
	void Game::MouseDown(int button)
	{
		manager.MouseDown(button);
	}
	void Game::MouseMove(int x, int y)
	{
		manager.MouseMove(x, y);
	}
	void Game::KeyUp(int key)
	{
		manager.KeyUp(key);
	}
	void Game::KeyDown(int key)
	{
		manager.KeyDown(key);
	}
	
};