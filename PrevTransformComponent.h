#pragma once
#include "Components.h"

/*
NOTE:
This is a previous transform, it keeps the previous transformation
*/

class PrevTransformComponent : public TransformComponent
{
public:
	/**/
	PrevTransformComponent() : TransformComponent()
	{
	}
	PrevTransformComponent(float x, float y) : TransformComponent(x, y)
	{
	}
	PrevTransformComponent(Vector2D set_position) : TransformComponent(set_position)
	{
	}
	/**/
};

