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
			if (type == 5)
			{
				AddAccelerator(x * tileSize, y * tileSize, set_color);
			}
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::AddAccelerator(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());

	tile.addComponent<TransformComponent>(xpos, ypos);
	tile.addComponent<ShapeComponent>(t_rectangle);
	
	//Up and Down
	tile.addComponent<AcceleratorComponent>(Vector2D(0, -0.0001));
	
	//Left and Right
	//tile.addComponent<AcceleratorComponent>(Vector2D(0.0002, 0));

	tile.getComponent<ShapeComponent>().pShape->color = set_color;
	tile.getComponent<ShapeComponent>().pShape->params["width"] = tileSize;
	tile.getComponent<ShapeComponent>().pShape->params["height"] = tileSize;
	
	tile.getComponent<ShapeComponent>().pShape->params["accelerator_up"] = 1.0;

	//tile.getComponent<ShapeComponent>().pShape->params["accelerator_down"] = 1.0;

	tile.addGroup(Game::groupAccelerators);
}


void Map::AddTile(int xpos, int ypos, Pixel set_color)
{
	auto& tile(manager.addObject());
	
	tile.addComponent<TransformComponent>(xpos, ypos);
	tile.addComponent<ShapeComponent>(t_rectangle);
	tile.getComponent<ShapeComponent>().pShape->color = set_color;
	tile.getComponent<ShapeComponent>().pShape->params["width"] = tileSize;
	tile.getComponent<ShapeComponent>().pShape->params["height"] = tileSize;
	tile.getComponent<ShapeComponent>().pShape->params["basic_tile"] = 1.0;


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
	tile.getComponent<ShapeComponent>().pShape->params["flag"] = 1.0;

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
	tile.getComponent<ShapeComponent>().pShape->params["skull"] = 1.0;

	tile.addGroup(Game::groupSkulls);
}