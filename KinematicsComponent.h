#pragma once
#include "Components.h"

#define GRAVITY 0.0001
#define FRICTION -0.0001

/*
Purpose:
- Move the object (player) around using velocity and acceleration

Used by the player.
*/

class KinematicsComponent : public Component
{
public:
	bool freeze = false;
	Vector2D velocity;
	Vector2D acceleration;
	float speed;
	float max_speed;

	TransformComponent* ptransformComponent;

	float bounce_coefficient = 1.0;

	KinematicsComponent()
	{
		velocity = Vector2D(0, 0);
		acceleration = Vector2D(0, 0);
		max_speed = 0.0f;
		speed = 0.0f;
	}
	KinematicsComponent(float set_speed, float set_max_speed)
	{
		velocity = Vector2D(0, 0);
		acceleration = Vector2D(FRICTION, GRAVITY);
		max_speed = set_max_speed;
		speed = set_speed;
	}

	void Init();
	
	void Tick(float delta);
};