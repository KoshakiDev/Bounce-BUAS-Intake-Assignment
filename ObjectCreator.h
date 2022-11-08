#pragma once
#include "Components.h"

enum ObjectType {
	t_ball,
	t_balloon,
	t_rock,
	t_basic, 
	t_flag, 
	t_skull, 
	t_boostUp,
	t_boostDown,
	t_boostRight,
	t_boostLeft,
	t_moveUp,
	t_moveDown,
	t_moveRight,
	t_moveLeft
};

class ObjectCreator
{
public:
	ObjectCreator() {}
	~ObjectCreator() {}

	static ObjectType DecodeSign(char c);

	static void Create(ObjectType type, float xpos, float ypos, Pixel set_color, float tile_size);

	static void CreatePlayer(Object& player, float xpos, float ypos, Pixel set_color, float tile_size);

	static void AddBasicComponents(Object& tile, float xpos, float ypos, Pixel set_color, float tile_size);

	static void Basic(Object& tile);
	static void Flag(Object& tile);
	static void Skull(Object& tile);

	static void Boost(Object& tile, Vector2D acceleration);

	static void BoostUp(Object& tile);
	static void BoostDown(Object& tile);
	static void BoostRight(Object& tile);
	static void BoostLeft(Object& tile);

	static void Move(Object& tile, Vector2D offset_vector, Vector2D velocity);

	static void MoveUp(Object& tile);
	static void MoveDown(Object& tile);
	static void MoveRight(Object& tile);
	static void MoveLeft(Object& tile);
};
