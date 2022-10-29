#pragma once
#include "Components.h"


class AcceleratorComponent : public Component
{
public:
	Vector2D acceleration;
	
	AcceleratorComponent()
	{
		acceleration = Vector2D(0, -1);
	}
	AcceleratorComponent(float x, float y)
	{
		acceleration = Vector2D(x, y);
	}
	AcceleratorComponent(Vector2D set_acceleration)
	{
		acceleration = set_acceleration;
	}

	void Init()
	{
	}
	void Tick(float delta)
	{
	}
	void Draw(Surface* screen) {}
};