#pragma once
#include "Components.h"

class Map
{
public:
	Map(float set_tileSize)
	{
		tileSize = set_tileSize;
	}
	~Map();

	void LoadMap(string path, int sizeX, int sizeY, Pixel set_color);
	void AddTile(int xpos, int ypos, Pixel set_color);
private:
	float tileSize;

};
