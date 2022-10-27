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
			int type = atoi(&c);
			//srcY = atoi(&c) * tileSize;

			//todo: add tile factory
			if (type == 1)
			{
				AddTile(x * tileSize, y * tileSize, set_color);
			}
			if (type == 2)
			{
				AddFlag(x * tileSize, y * tileSize, set_color);
			}
			if (type == 3)
			{
				AddSkull(x * tileSize, y * tileSize, set_color);
			}
			if (type == 4)
			{
				level_beginning = Vector2D(x * tileSize * 1.5, y * tileSize * 1.5);
			}
			mapFile.ignore();
		}
	}
	mapFile.close();
}


void Map::AddTile(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());
	
	tile.addComponent<TransformComponent>(xpos, ypos);
	tile.addComponent<ShapeComponent>(t_rectangle);
	tile.getComponent<ShapeComponent>().pShape->color = set_color;
	tile.getComponent<ShapeComponent>().pShape->params["width"] = tileSize;
	tile.getComponent<ShapeComponent>().pShape->params["height"] = tileSize;
	tile.getComponent<ShapeComponent>().pShape->params["tile_type"] = 1.0;


	tile.addGroup(Game::groupMap);
}

void Map::AddFlag(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());

	tile.addComponent<TransformComponent>(xpos, ypos);
	tile.addComponent<ShapeComponent>(t_rectangle);
	tile.getComponent<ShapeComponent>().pShape->color = set_color;
	tile.getComponent<ShapeComponent>().pShape->params["width"] = tileSize;
	tile.getComponent<ShapeComponent>().pShape->params["height"] = tileSize;
	tile.getComponent<ShapeComponent>().pShape->params["tile_type"] = 2.0;

	tile.addGroup(Game::groupFlags);
}

void Map::AddSkull(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());

	tile.addComponent<TransformComponent>(xpos, ypos);
	tile.addComponent<ShapeComponent>(t_rectangle);
	tile.getComponent<ShapeComponent>().pShape->color = set_color;
	tile.getComponent<ShapeComponent>().pShape->params["width"] = tileSize;
	tile.getComponent<ShapeComponent>().pShape->params["height"] = tileSize;
	tile.getComponent<ShapeComponent>().pShape->params["tile_type"] = 3.0;

	tile.addGroup(Game::groupSkulls);
}