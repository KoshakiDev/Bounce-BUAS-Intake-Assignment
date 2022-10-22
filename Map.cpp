#include "Components.h"
#include "Game.h"
#include <fstream>
#define TILE_SIZE 32

extern Manager manager;

void Map::LoadMap(string path, int sizeX, int sizeY)
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
			if (type == 1)
			{
				AddTile(x * tileSize, y * tileSize);
			}
			mapFile.ignore();
		}
	}
	/*
	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("TERRAIN");
				//tcol.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}
	*/
	mapFile.close();
}


void Map::AddTile(int xpos, int ypos)
{
	auto& tile(manager.addObject());
	
	tile.addComponent<TransformComponent>(xpos, ypos);
	tile.addComponent<ShapeComponent>(t_rectangle);
	tile.getComponent<ShapeComponent>().pShape->params["width"] = tileSize;
	tile.getComponent<ShapeComponent>().pShape->params["height"] = tileSize;


	//tile.addGroup(Game::groupMap);
}