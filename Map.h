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

	void LoadMap(string path, int sizeX, int sizeY);
	void AddTile(int xpos, int ypos);
private:
	float tileSize;

};
