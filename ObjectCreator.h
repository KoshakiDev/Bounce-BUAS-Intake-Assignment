#pragma once
#include "Components.h"



class ObjectCreator
{
public:
	ObjectCreator() {}
	~ObjectCreator() {}

	static ObjectType DecodeSign(char c);

	static void Create(ObjectType type, float xpos, float ypos, Pixel set_color, float tile_size);

	static void CreatePlayer(Object& player, float xpos, float ypos, Pixel set_color, float tile_size, ObjectType set_type);

	static void AddBasicComponents(Object& tile, float xpos, float ypos, Pixel set_color, float tile_size, ObjectType set_type);

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
