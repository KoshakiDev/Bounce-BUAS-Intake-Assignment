#include "Components.h"
#include "Game.h"

/*
Purpose:
- Create level layout using tiles

*/

extern Manager manager;

void ObjectCreator::CreatePlayer(Object& player, float xpos, float ypos, Pixel set_color, float tile_size)
{
	player.addComponent<TransformComponent>(xpos + 0.5 * tile_size, ypos + 0.5 * tile_size);
	player.addComponent<KinematicsComponent>(0.1, 0.5);
	player.addComponent<ShapeComponent>(t_circle);
	player.getComponent<ShapeComponent>().pShape->color = set_color;
	player.getComponent<ShapeComponent>().pShape->params["radius"] = tile_size / 2;
	player.addGroup(Game::groupPlayers);
}

void ObjectCreator::AddBasicComponents(Object& tile, float xpos, float ypos, Pixel set_color, float tile_size)
{
	tile.addComponent<TransformComponent>(xpos, ypos);
	tile.addComponent<ShapeComponent>(t_rectangle);
	tile.getComponent<ShapeComponent>().pShape->color = set_color;
	tile.getComponent<ShapeComponent>().pShape->params["width"] = tile_size;
	tile.getComponent<ShapeComponent>().pShape->params["height"] = tile_size;
}

ObjectType ObjectCreator::DecodeSign(char c)
{
	if (c == '#')
	{
		return t_basic;
	}
	if (c == 'F')
	{
		return t_flag;
	}
	if (c == 'X')
	{
		return t_skull;
	}
	if (c == '@')
	{
		return t_ball;
	}
	if (c == '^')
	{
		return t_boostUp;
	}
	if (c == 'v')
	{
		return t_boostDown;
	}
	if (c == '<')
	{
		return t_boostLeft;
	}
	if (c == '>')
	{
		return t_boostRight;
	}
	if (c == 'U')
	{
		return t_moveUp;
	}
	if (c == 'D')
	{
		return t_moveDown;
	}
	if (c == 'L')
	{
		return t_moveLeft;
	}
	if (c == 'R')
	{
		return t_moveRight;
	}
}


void ObjectCreator::Create(ObjectType type, float xpos, float ypos, Pixel set_color, float tile_size)
{
	auto& tile(manager.addObject());
	if (type == t_ball)
	{
		CreatePlayer(tile, xpos, ypos, set_color, tile_size);
		return;
	}

	AddBasicComponents(tile, xpos, ypos, set_color, tile_size);

	if (type == t_basic)
		Basic(tile);
	else if (type == t_flag)
		Flag(tile);
	else if (type == t_skull)
		Skull(tile);
	else if (type == t_boostUp)
		BoostUp(tile);
	else if (type == t_boostDown)
		BoostDown(tile);
	else if (type == t_boostLeft)
		BoostLeft(tile);
	else if (type == t_boostRight)
		BoostRight(tile);
	else if (type == t_moveUp)
		MoveUp(tile);
	else if (type == t_moveDown)
		MoveDown(tile);
	else if (type == t_moveRight)
		MoveRight(tile);
	else if (type == t_moveLeft)
		MoveLeft(tile);
}

void ObjectCreator::Basic(Object& tile)
{
	tile.getComponent<ShapeComponent>().pShape->material_type["basic_tile"] = true;
	tile.addGroup(Game::groupMap);
}

void ObjectCreator::Flag(Object& tile)
{
	tile.getComponent<ShapeComponent>().pShape->material_type["flag"] = true;
	tile.addGroup(Game::groupFlags);
}

void ObjectCreator::Skull(Object& tile)
{
	tile.getComponent<ShapeComponent>().pShape->material_type["skull"] = true;
	tile.addGroup(Game::groupSkulls);
}

void ObjectCreator::Move(Object& tile, Vector2D offset_vector, Vector2D velocity)
{
	float tile_size = tile.getComponent<ShapeComponent>().pShape->params["height"];
	float speed = 0.1;
	offset_vector *= tile_size * 2;
	velocity *= speed;
	Vector2D final_position_1 = tile.getComponent<TransformComponent>().position + offset_vector;
	Vector2D final_position_2 = tile.getComponent<TransformComponent>().position - offset_vector;
	tile.addComponent<MovingTileComponent>(final_position_1, final_position_2, velocity);
	Basic(tile);
}

void ObjectCreator::MoveUp(Object& tile)
{
	Vector2D offset_vector = Vector2D(0, 1);
	Vector2D velocity = Vector2D(0, -1);
	
	Move(tile, offset_vector, velocity);
}

void ObjectCreator::MoveDown(Object& tile)
{
	Vector2D offset_vector = Vector2D(0, 1);
	Vector2D velocity = Vector2D(0, 1);

	Move(tile, offset_vector, velocity);
}

void ObjectCreator::MoveLeft(Object& tile)
{
	Vector2D offset_vector = Vector2D(1, 0);
	Vector2D velocity = Vector2D(-1, 0);

	Move(tile, offset_vector, velocity);
}

void ObjectCreator::MoveRight(Object& tile)
{
	Vector2D offset_vector = Vector2D(1, 0);
	Vector2D velocity = Vector2D(1, 0);

	Move(tile, offset_vector, velocity);
}

void ObjectCreator::Boost(Object& tile, Vector2D acceleration)
{
	tile.addComponent<AcceleratorComponent>(acceleration);
	tile.addGroup(Game::groupAccelerators);
}

void ObjectCreator::BoostUp(Object& tile)
{
	Vector2D acceleration = Vector2D(0, -0.0001);
	tile.getComponent<ShapeComponent>().pShape->material_type["accelerator_up"] = true;
	Boost(tile, acceleration);
}

void ObjectCreator::BoostDown(Object& tile)
{
	Vector2D acceleration = Vector2D(0, 0.0001);
	tile.getComponent<ShapeComponent>().pShape->material_type["accelerator_down"] = true;
	Boost(tile, acceleration);
}

void ObjectCreator::BoostLeft(Object& tile)
{
	Vector2D acceleration = Vector2D(-0.0002, 0);
	tile.getComponent<ShapeComponent>().pShape->material_type["accelerator_left"] = true;

	Boost(tile, acceleration);
}

void ObjectCreator::BoostRight(Object& tile)
{
	Vector2D acceleration = Vector2D(0.0002, 0);
	tile.getComponent<ShapeComponent>().pShape->material_type["accelerator_right"] = true;
	Boost(tile, acceleration);
}