#pragma once
#include "Components.h"

/*
Purpose:
- Receives 2 positions to oscillate between

Used by moving tiles
*/

class MovingTileComponent : public Component
{
public:
	Vector2D velocity;
	
	TransformComponent* ptransformComponent;
	Vector2D final_position_1;
	Vector2D final_position_2;
	
	MovingTileComponent()
	{
		velocity = Vector2D(0, 0);
		final_position_1 = Vector2D(0, 0);
		final_position_2 = Vector2D(0, 0);
	}
	MovingTileComponent(Vector2D set_final_position_1, Vector2D set_final_position_2, Vector2D set_velocity)
	{
		velocity = set_velocity;
		final_position_1 = set_final_position_1;
		final_position_2 = set_final_position_2;
	}

	void Init();
	
	void Tick(float delta);
	
};