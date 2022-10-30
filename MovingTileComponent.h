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

	void Init()
	{
		if (!owner->hasComponent<TransformComponent>())
		{
			owner->addComponent<TransformComponent>();
		}
		ptransformComponent = &owner->getComponent<TransformComponent>();
	}
	void Tick(float delta)
	{
		if (ptransformComponent->position.x >= final_position_1.x && ptransformComponent->position.y >= final_position_1.y)
		{
			velocity = -velocity;
			ptransformComponent->position = final_position_1;
		}
		if (ptransformComponent->position.x <= final_position_2.x && ptransformComponent->position.y <= final_position_2.y)
		{
			velocity = -velocity;
			ptransformComponent->position = final_position_2;
		}
		ptransformComponent->position = ptransformComponent->position + velocity * delta;
	}
};