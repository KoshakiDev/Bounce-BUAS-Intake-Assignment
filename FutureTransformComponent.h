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

class FutureTransformComponent : public TransformComponent
{
public:
	FutureTransformComponent() : TransformComponent()
	{
	}
	
	FutureTransformComponent(float x, float y) : TransformComponent(x, y)
	{
	}

	FutureTransformComponent(Vector2D set_position) : TransformComponent(set_position)
	{
	}
};