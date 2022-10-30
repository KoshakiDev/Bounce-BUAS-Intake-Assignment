#pragma once
#include "Components.h"

/*
Purpose: 
- Contain the object's position (Vector2D)
*/

class TransformComponent : public Component
{
public:
	TransformComponent()
	{
		position.x = 0.0f;
		position.y = 0.0f;
	}
	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}	
	TransformComponent(Vector2D set_position) 
	{ 
		position = set_position;
	}
	
	void Translate(Vector2D set_translate)
	{
		position += set_translate;
	}
	Vector2D position = Vector2D(0, 0);
};

