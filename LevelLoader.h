#pragma once
#include "Components.h"

class LevelLoader
{
public:
	LevelLoader(float set_tileSize)
	{
		tileSize = set_tileSize;
	}
	~LevelLoader();

	void LoadMap(string path, int sizeX, int sizeY, Pixel set_color);

private:
	float tileSize;
};
