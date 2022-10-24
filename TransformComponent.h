#pragma once
#include "Components.h"

/*
NOTE: 

This code was borrowed from Snow Wars, then modified in according to "Lets Make Games" tutorial.

Transform contains the 2D position vector.
Every other object in the game #includes this header.

Initially I wanted to include rotation, but then I realized that it would be incompatible with Surface. 
Surface does not have a built in understanding of rotation. 
This would mean that I have to drastically modify the given template

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

