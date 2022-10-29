#pragma once
#include "Components.h"


class MovingTileComponent : public Component
{
public:
	Vector2D velocity;
	float speed;
	
	TransformComponent* ptransformComponent;
	Vector2D travel_vector;
	Vector2D original_position;
	
	MovingTileComponent()
	{
		velocity = Vector2D(0, 0);
		travel_vector = Vector2D(0, 1);
		speed = 0.0f;
	}
	MovingTileComponent(Vector2D set_travel_vector, float set_speed)
	{
		velocity = Vector2D(0, 0);
		travel_vector = set_travel_vector;
		speed = set_speed;
	}

	void Init()
	{
		if (!owner->hasComponent<TransformComponent>())
		{
			owner->addComponent<TransformComponent>();
		}
		ptransformComponent = &owner->getComponent<TransformComponent>();
		original_position = owner->getComponent<TransformComponent>().position;

	}
	void Tick(float delta)
	{
		/**
		Vector2D change_in_position = ptransformComponent->position - original_position;
		if (change_in_position.x == travel_vector.x && change_in_position.y == travel_vector.y)
		{
			velocity = -velocity;
		}
		ptransformComponent->position = ptransformComponent->position + velocity * delta;
		/**/
	}
	void Draw(Surface* screen) {}

	void MouseMove(int x, int y) {}

	void KeyUp(int key)
	{
	}

	void KeyDown(int key)
	{

	}
};