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

LevelLoader* tilemap;

Pixel background_color = moldy_white;



// Getting references for each object category respectively
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
int current_level = -1;

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		tilemap = new LevelLoader(TILE_SIZE);
		NextLevel();
	}

	void Game::ClearLevel()
	{
		for (auto& t : players)
		{
			t->destroy();
		}
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
	}

	void Game::LoadLevel()
	{
		if (background_color == moldy_white)
		{
			tilemap->LoadMap(path[current_level], 25, 20, moldy_black);
		}
		else if (background_color == moldy_black)
		{
			tilemap->LoadMap(path[current_level], 25, 20, moldy_white);
		}
	}

	void Game::NextLevel()
	{
		ClearLevel();
		current_level++;
		LoadLevel();
	}

	void Game::RestartLevel()
	{
		ClearLevel();
		LoadLevel();
	}

	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		ClearLevel();
	}
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------

	void Game::CheckTileCollision(float delta)
	{
		for (auto& player : players)
		{
			for (auto& t : tiles)
			{
				Vector2D penetration_normal = Vector2D(-1, -1);
				float penetration_depth = 0;

				if (Collision::Check(
					player->getComponent<ShapeComponent>().pShape,
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
						player->getComponent<KinematicsComponent>().velocity.x *= -1 * abs(penetration_normal.x);
					}
					else if (penetration_normal.y != 0)
					{
						player->getComponent<KinematicsComponent>().velocity.y *= -1 * abs(penetration_normal.y);
					}
					player->getComponent<KinematicsComponent>().velocity *= player->getComponent<KinematicsComponent>().bounce_coefficient;

					// Remove penetration (penetration epsilon added to handle infinitely small penetration):
					player->getComponent<TransformComponent>().Translate(penetration_normal * (penetration_depth + 0.0001f));
				}
			}
		}

	}

	void Game::CheckSkullCollision(float delta)
	{
		bool is_dead = false;
		for (auto& player : players)
		{
			for (auto& t : skulls)
			{
				Vector2D penetration_normal = Vector2D(-1, -1);
				float penetration_depth = 0;

				if (Collision::Check(
					player->getComponent<ShapeComponent>().pShape,
					t->getComponent<ShapeComponent>().pShape,
					penetration_normal,
					penetration_depth)
					)
				{
					is_dead = true;
				}
			}
		}
		if (is_dead)
		{
			RestartLevel();
		}
	}
	void Game::CheckAcceleratorCollision(float delta) 
	{
		for (auto& player : players)
		{
			for (auto& t : accelerators)
			{
				Vector2D penetration_normal = Vector2D(-1, -1);
				float penetration_depth = 0;

				if (Collision::Check(
					player->getComponent<ShapeComponent>().pShape,
					t->getComponent<ShapeComponent>().pShape,
					penetration_normal,
					penetration_depth)
					)
				{
					player->getComponent<KinematicsComponent>().velocity.y = Clamp(player->getComponent<KinematicsComponent>().velocity.y + t->getComponent<AcceleratorComponent>().acceleration.y * delta, -player->getComponent<KinematicsComponent>().max_speed, player->getComponent<KinematicsComponent>().max_speed);
					player->getComponent<KinematicsComponent>().velocity.x = Clamp(player->getComponent<KinematicsComponent>().velocity.x + t->getComponent<AcceleratorComponent>().acceleration.x * delta, -player->getComponent<KinematicsComponent>().max_speed, player->getComponent<KinematicsComponent>().max_speed);

				}
			}
		}
	}

	void Game::CheckFlagCollision(float delta)
	{
		for (auto& player : players)
		{
			for (auto& t : flags)
			{
				Vector2D penetration_normal = Vector2D(-1, -1);
				float penetration_depth = 0;

				if (Collision::Check(
					player->getComponent<ShapeComponent>().pShape,
					t->getComponent<ShapeComponent>().pShape,
					penetration_normal,
					penetration_depth)
					)
				{
					NextLevel();
				}
			}
		}
	}

	void Game::Tick(float delta)
	{
		manager.refresh();
		for (auto& player : players)
		{
			if (isnan(player->getComponent<TransformComponent>().position.x) || isnan(player->getComponent<TransformComponent>().position.y))
			{
				RestartLevel();
			}
		}
		
		manager.Tick(delta);
		
		CheckTileCollision(delta);
		CheckAcceleratorCollision(delta);
		CheckFlagCollision(delta);
		CheckSkullCollision(delta);

		Draw(screen);
	}

	void Game::Draw(Surface* screen)
	{
		screen->Clear(background_color);
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