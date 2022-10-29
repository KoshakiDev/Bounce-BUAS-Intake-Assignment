#include "Components.h"
#include "Game.h"
#include <fstream>
#define TILE_SIZE 32

extern Manager manager;
extern Vector2D level_beginning;

void Map::LoadMap(string path, int sizeX, int sizeY, Pixel set_color)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			
			//todo: add tile factory
			if (c == '#')
			{
				AddTile(x * tileSize, y * tileSize, set_color);
			}
			if (c == 'F')
			{
				AddFlag(x * tileSize, y * tileSize, set_color);
			}
			if (c == 'X')
			{
				AddSkull(x * tileSize, y * tileSize, set_color);
			}
			if (c == '@')
			{
				level_beginning = Vector2D(x * tileSize, y * tileSize);
			}
			if (c == '^')
			{
				AddAcceleratorUp(x * tileSize, y * tileSize, set_color);
			}
			if (c == 'v')
			{
				AddAcceleratorDown(x * tileSize, y * tileSize, set_color);
			}
			if (c == '<')
			{
				AddAcceleratorLeft(x * tileSize, y * tileSize, set_color);
			}
			if (c == '>')
			{
				AddAcceleratorRight(x * tileSize, y * tileSize, set_color);
			}
			if (c == 'U')
			{
				AddMovingTileUp(x * tileSize, y * tileSize, set_color);
			}
			if (c == 'D')
			{
				AddMovingTileDown(x * tileSize, y * tileSize, set_color);
			}
			if (c == 'L')
			{
				AddMovingTileLeft(x * tileSize, y * tileSize, set_color);
			}
			if (c == 'R')
			{
				AddMovingTileRight(x * tileSize, y * tileSize, set_color);
			}
		}
		mapFile.ignore();
	}
	mapFile.close();
}

void Map::AddBasicComponents(Object& tile, int xpos, int ypos, Pixel set_color)
{
	tile.addComponent<TransformComponent>(xpos, ypos);
	tile.addComponent<ShapeComponent>(t_rectangle);
	tile.getComponent<ShapeComponent>().pShape->color = set_color;
	tile.getComponent<ShapeComponent>().pShape->params["width"] = tileSize;
	tile.getComponent<ShapeComponent>().pShape->params["height"] = tileSize;
}

void Map::AddMovingTileUp(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());
	AddBasicComponents(tile, xpos, ypos, set_color);

	tile.addComponent<MovingTileComponent>(Vector2D(xpos, ypos + 2 * tileSize), Vector2D(xpos, ypos - 2 * tileSize), Vector2D(0, -0.1));
	tile.getComponent<ShapeComponent>().pShape->material_type["basic_tile"] = true;
	tile.addGroup(Game::groupMap);
}

void Map::AddMovingTileDown(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());
	AddBasicComponents(tile, xpos, ypos, set_color);

	tile.addComponent<MovingTileComponent>(Vector2D(xpos, ypos + 2 * tileSize), Vector2D(xpos, ypos - 2 * tileSize), Vector2D(0, 0.1));
	tile.getComponent<ShapeComponent>().pShape->material_type["basic_tile"] = true;
	tile.addGroup(Game::groupMap);
}

void Map::AddMovingTileLeft(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());
	AddBasicComponents(tile, xpos, ypos, set_color);

	tile.addComponent<MovingTileComponent>(Vector2D(xpos + 2 * tileSize, ypos), Vector2D(xpos - 2 * tileSize, ypos), Vector2D(-0.1, 0));
	tile.getComponent<ShapeComponent>().pShape->material_type["basic_tile"] = true;
	tile.addGroup(Game::groupMap);
}

void Map::AddMovingTileRight(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());
	AddBasicComponents(tile, xpos, ypos, set_color);

	tile.addComponent<MovingTileComponent>(Vector2D(xpos + 2 * tileSize, ypos), Vector2D(xpos - 2 * tileSize, ypos), Vector2D(0.1, 0));
	tile.getComponent<ShapeComponent>().pShape->material_type["basic_tile"] = true;
	tile.addGroup(Game::groupMap);
}


void Map::AddAcceleratorUp(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());
	AddBasicComponents(tile, xpos, ypos, set_color);
	
	tile.addComponent<AcceleratorComponent>(Vector2D(0, -0.0001));

	tile.getComponent<ShapeComponent>().pShape->material_type["accelerator_up"] = true;
	tile.addGroup(Game::groupAccelerators);
}

void Map::AddAcceleratorDown(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());
	AddBasicComponents(tile, xpos, ypos, set_color);

	tile.addComponent<AcceleratorComponent>(Vector2D(0, 0.0001));

	tile.getComponent<ShapeComponent>().pShape->material_type["accelerator_down"] = true;
	tile.addGroup(Game::groupAccelerators);
}

void Map::AddAcceleratorLeft(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());
	AddBasicComponents(tile, xpos, ypos, set_color);

	tile.addComponent<AcceleratorComponent>(Vector2D(-0.0002, 0));

	tile.getComponent<ShapeComponent>().pShape->material_type["accelerator_left"] = true;
	tile.addGroup(Game::groupAccelerators);
}

void Map::AddAcceleratorRight(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());
	AddBasicComponents(tile, xpos, ypos, set_color);

	tile.addComponent<AcceleratorComponent>(Vector2D(0.0002, 0));

	tile.getComponent<ShapeComponent>().pShape->material_type["accelerator_right"] = true;
	tile.addGroup(Game::groupAccelerators);
}


void Map::AddTile(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());
	
	AddBasicComponents(tile, xpos, ypos, set_color);

	tile.getComponent<ShapeComponent>().pShape->material_type["basic_tile"] = true;
	tile.addGroup(Game::groupMap);
}

void Map::AddFlag(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());

	AddBasicComponents(tile, xpos, ypos, set_color);

	tile.getComponent<ShapeComponent>().pShape->material_type["flag"] = true;

	tile.addGroup(Game::groupFlags);
}

void Map::AddSkull(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());

	AddBasicComponents(tile, xpos, ypos, set_color);

	tile.getComponent<ShapeComponent>().pShape->material_type["skull"] = true;

	tile.addGroup(Game::groupSkulls);
}