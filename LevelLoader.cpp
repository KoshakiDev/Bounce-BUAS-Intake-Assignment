#include "Components.h"
#include <fstream>
#define TILE_SIZE 32

/*
Purpose:
- Load level from a file
*/

void LevelLoader::LoadMap(string path, int sizeX, int sizeY, Pixel set_color)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			ObjectCreator::Create(ObjectCreator::DecodeSign(c), float(x * tileSize), float(y * tileSize), set_color, tileSize);
		}
		mapFile.ignore();
	}
	mapFile.close();
}