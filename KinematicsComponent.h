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

	void Init() 
	{
		if (!owner->hasComponent<TransformComponent>())
		{
			owner->addComponent<TransformComponent>();
		}
		ptransformComponent = &owner->getComponent<TransformComponent>();
	}
	void Tick(float delta);
	void Draw(Surface* screen) {}

	void MouseMove(int x, int y) {}
	
	void KeyUp(int key)
	{
		//Remember that Y is flipped
		/**/
		if (key == SDL_SCANCODE_J) //Balloon
		{
			acceleration = Vector2D(FRICTION, -GRAVITY / 10);
			bounce_coefficient = 0.2;

		}
		if (key == SDL_SCANCODE_K) // Ball
		{
			acceleration = Vector2D(FRICTION, GRAVITY);
			bounce_coefficient = 0.99;
		}
		if (key == SDL_SCANCODE_L) //Rock
		{
			acceleration = Vector2D(FRICTION, GRAVITY * 2);
			bounce_coefficient = 0.0;
		}
		/**/
		
		if (key == SDL_SCANCODE_D)
		{
			velocity.x = clamp(velocity.x + (speed), -max_speed, max_speed);
		}
		if (key == SDL_SCANCODE_A)
		{
			velocity.x = clamp(velocity.x + (-speed), -max_speed, max_speed);
		}
		clamp(velocity.x, -max_speed, max_speed);
		clamp(velocity.y, -max_speed, max_speed);
	}
};