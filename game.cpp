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

Pixel background_color = moldy_white;

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

auto& skulls(manager.getGroup(Game::groupSkulls));
auto& flags(manager.getGroup(Game::groupFlags));

auto& accelerators(manager.getGroup(Game::groupAccelerators));


string path[15] = {
	"tutorial_flag_a.map",
	"tutorial_flag_d.map",
	"tutorial_skull.map",
	"tutorial_accelerator.map",
	"tutorial_rock.map",
	"tutorial_balloon.map",
	"tutorial_moving_tile.map",
	"1.map",
	"2.map",
	"3.map",
	"win.map"
};
Vector2D level_beginning = Vector2D(0, 0);
int current_level = -1;

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		//Creating the player

		player.addComponent<TransformComponent>(0, 0);
		player.addComponent<KinematicsComponent>(0.1, 0.5);
		player.addComponent<ShapeComponent>(t_circle);
		player.getComponent<ShapeComponent>().pShape->params["radius"] = TILE_SIZE / 2;
		player.getComponent<ShapeComponent>().pShape->color = moldy_black;

		tilemap = new Map(TILE_SIZE);

		ClearLevel();
	}
	
	void Game::ResetPlayerPosition()
	{
		player.getComponent<TransformComponent>().position = level_beginning;
		player.getComponent<KinematicsComponent>().velocity = Vector2D(0, 0);

	}

	void Game::ClearLevel()
	{
		for (auto& t : tiles)
		{
			t->destroy();
		}
		for (auto& t : flags)
		{
			t->destroy();
		}
		for (auto& t : skulls)
		{
			t->destroy();
		}
		for (auto& t : accelerators)
		{
			t->destroy();
		}
		current_level++;
		cout << "current level :" << current_level << endl;

		if (background_color == moldy_white)
		{
			tilemap->LoadMap(path[current_level], 25, 20, moldy_black);
		}
		else if (background_color == moldy_black)
		{
			tilemap->LoadMap(path[current_level], 25, 20, moldy_white);
		}
		ResetPlayerPosition();
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
		if (isnan(player.getComponent<TransformComponent>().position.x) || isnan(player.getComponent<TransformComponent>().position.y))
		{
			ResetPlayerPosition();
		}
		manager.refresh();
		manager.Tick(delta);
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
				player.getComponent<KinematicsComponent>().velocity *= player.getComponent<KinematicsComponent>().bounce_coefficient;

				// Remove penetration (penetration epsilon added to handle infinitely small penetration):
				player.getComponent<TransformComponent>().Translate(penetration_normal * (penetration_depth + 0.0001f));
			}
		}
		
		for (auto& t : skulls)
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
				ResetPlayerPosition();
			}
		}

		for (auto& t : flags)
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
				ClearLevel();
			}
		}

		for (auto& t : accelerators)
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
				player.getComponent<KinematicsComponent>().velocity.y = Clamp(player.getComponent<KinematicsComponent>().velocity.y + t->getComponent<AcceleratorComponent>().acceleration.y * delta, -player.getComponent<KinematicsComponent>().max_speed, player.getComponent<KinematicsComponent>().max_speed);
				player.getComponent<KinematicsComponent>().velocity.x = Clamp(player.getComponent<KinematicsComponent>().velocity.x + t->getComponent<AcceleratorComponent>().acceleration.x * delta, -player.getComponent<KinematicsComponent>().max_speed, player.getComponent<KinematicsComponent>().max_speed);

			}
		}


		/*
		Well, the trick there is to not let the circle intersect with the box in the first place. 
		When you move you check if there's something at your new position, and if not, you move. 
		Not the other way around where you move and then check : )
		*/

		Draw(screen);
	}

	void Game::Draw(Surface* screen)
	{
		screen->Clear(background_color);
		manager.Draw(screen);
		//const char name = "level %i";
		//screen->Print(name, 50, 50, red);
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
		if (key == SDL_SCANCODE_Z)
		{
			if (background_color == moldy_white)
			{
				background_color = moldy_black;
			}
			else if (background_color == moldy_black)
			{
				background_color = moldy_white;
			}
		}
	}
	void Game::KeyDown(int key)
	{
		manager.KeyDown(key);
	}
	
};