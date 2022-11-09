#include "Components.h"
#include "Game.h"

/*
Purpose:
- Create level layout using tiles

*/
extern Pixel moldy_white, moldy_black, red, yellow, green, true_white, true_black;

extern Manager manager;

void ObjectCreator::CreatePlayer(Object& player, float xpos, float ypos, Pixel set_color, float tile_size, ObjectType set_type)
{
	player.addComponent<TransformComponent>(xpos + 0.5 * tile_size, ypos + 0.5 * tile_size);
	player.addComponent<KinematicsComponent>(0.1, 0.5);
	player.addComponent<ShapeComponent>(t_circle);
	player.getComponent<ShapeComponent>().pShape->color = true_white;
	player.getComponent<ShapeComponent>().pShape->object_type = set_type;
	player.getComponent<ShapeComponent>().pShape->params["radius"] = tile_size / 2;
	player.addComponent<PlayerComponent>();

	player.addGroup(Game::groupPlayers);
}

void ObjectCreator::AddBasicComponents(Object& tile, float xpos, float ypos, Pixel set_color, float tile_size, ObjectType set_type)
{
	tile.addComponent<TransformComponent>(xpos, ypos);
	tile.addComponent<ShapeComponent>(t_rectangle);
	tile.getComponent<ShapeComponent>().pShape->color = set_color;
	tile.getComponent<ShapeComponent>().pShape->object_type = set_type;
	tile.getComponent<ShapeComponent>().pShape->params["width"] = tile_size;
	tile.getComponent<ShapeComponent>().pShape->params["height"] = tile_size;
}

ObjectType ObjectCreator::DecodeSign(char c)
{
	if (c == '#')
	{
		return t_basic;
	}
	else if (c == 'F')
	{
		return t_flag;
	}
	else if (c == 'X')
	{
		return t_skull;
	}
	else if (c == '@')
	{
		return t_ball;
	}
	else if (c == '^')
	{
		return t_boostUp;
	}
	else if (c == 'v')
	{
		return t_boostDown;
	}
	else if (c == '<')
	{
		return t_boostLeft;
	}
	else if (c == '>')
	{
		return t_boostRight;
	}
	else if (c == 'U')
	{
		return t_moveUp;
	}
	else if (c == 'D')
	{
		return t_moveDown;
	}
	else if (c == 'L')
	{
		return t_moveLeft;
	}
	else if (c == 'R')
	{
		return t_moveRight;
	}
	else
	{
		return t_nothing;
	}
}


void ObjectCreator::Create(ObjectType type, float xpos, float ypos, Pixel set_color, float tile_size)
{
	if (type == t_nothing)
	{
		return;
	}
	auto& tile(manager.addObject());
	
	if (type == t_ball)
	{
		CreatePlayer(tile, xpos, ypos, set_color, tile_size, type);
		return;
	}

	AddBasicComponents(tile, xpos, ypos, set_color, tile_size, type);

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
	tile.addGroup(Game::groupMap);
}

void ObjectCreator::Flag(Object& tile)
{
	tile.getComponent<ShapeComponent>().pShape->color = true_white;
	tile.addGroup(Game::groupFlags);
}

void ObjectCreator::Skull(Object& tile)
{
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

void ObjectCreator::Boost(Object& tile, Vector2D set_acceleration)
{
	tile.addComponent<KinematicsComponent>();
	tile.getComponent<KinematicsComponent>().freeze = true;
	tile.getComponent<KinematicsComponent>().acceleration = set_acceleration;
	tile.addGroup(Game::groupAccelerators);
}

void ObjectCreator::BoostUp(Object& tile)
{
	Vector2D acceleration = Vector2D(0, -0.0001);
	Boost(tile, acceleration);
}

void ObjectCreator::BoostDown(Object& tile)
{
	Vector2D acceleration = Vector2D(0, 0.0001);
	Boost(tile, acceleration);
}

void ObjectCreator::BoostLeft(Object& tile)
{
	Vector2D acceleration = Vector2D(-0.0002, 0);
	Boost(tile, acceleration);
}

void ObjectCreator::BoostRight(Object& tile)
{
	Vector2D acceleration = Vector2D(0.0002, 0);
	Boost(tile, acceleration);
}