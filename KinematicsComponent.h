#pragma once
#include "Components.h"

#define GRAVITY 0.5
#define FRICTION 0.9


class KinematicsComponent : public Component
{
public:
	Vector2D velocity;
	Vector2D acceleration;
	float speed;
	float max_speed;

	TransformComponent* ptransformComponent;


	KinematicsComponent()
	{
		velocity = Vector2D(0, 0);
		acceleration = Vector2D(0, 0);
		max_speed = 0.0f;
		speed = 0.0f;
	}
	KinematicsComponent(float set_max_speed, float set_speed)
	{
		velocity = Vector2D(0, 0);
		acceleration = Vector2D(0, 0);
		max_speed = set_max_speed;
		speed = set_speed;
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
		velocity.x = Clamp(velocity.x + acceleration.x * delta, -max_speed, max_speed);
		velocity.y = Clamp(velocity.y + acceleration.y * delta, -max_speed, max_speed);
		acceleration = Vector2D(0, 0);
		ptransformComponent->position = ptransformComponent->position + velocity * delta;
	}
	void Draw(Surface* screen) {}
};