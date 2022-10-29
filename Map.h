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

	void AddBasicComponents(Object& tile, int xpos, int ypos, Pixel set_color);

	void AddTile(int xpos, int ypos, Pixel set_color);
	void AddFlag(int xpos, int ypos, Pixel set_color);
	void AddSkull(int xpos, int ypos, Pixel set_color);

	void AddAcceleratorUp(int xpos, int ypos, Pixel set_color);
	void AddAcceleratorDown(int xpos, int ypos, Pixel set_color);
	void AddAcceleratorRight(int xpos, int ypos, Pixel set_color);
	void AddAcceleratorLeft(int xpos, int ypos, Pixel set_color);

	void AddMovingTileUp(int xpos, int ypos, Pixel set_color);
	void AddMovingTileDown(int xpos, int ypos, Pixel set_color);
	void AddMovingTileRight(int xpos, int ypos, Pixel set_color);
	void AddMovingTileLeft(int xpos, int ypos, Pixel set_color);


private:
	float tileSize;

};
