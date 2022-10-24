#pragma once
#include "Components.h"

#define GRAVITY 0.001
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
	KinematicsComponent(float set_speed, float set_max_speed)
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
		acceleration = Vector2D(0, GRAVITY);
		velocity.x = Clamp(velocity.x + acceleration.x * delta, -max_speed, max_speed);
		velocity.y = Clamp(velocity.y + acceleration.y * delta, -max_speed, max_speed);
		ptransformComponent->position = ptransformComponent->position + velocity * delta;
	}
	void Draw(Surface* screen) {}

	void MouseMove(int x, int y)
	{
		//owner->getComponent<TransformComponent>().position = Vector2D(x, y);
	}

	void KeyDown(int key)
	{
		if (key == SDL_SCANCODE_E)
		{
			velocity = Vector2D(0, 0);
			//ptransformComponent->position = Vector2D(ScreenWidth / 2, ScreenHeight / 2);
		}
		//Remember that Y is flipped

		if (key == SDL_SCANCODE_W)
		{
			velocity.y = clamp(velocity.y + (-speed), -max_speed, max_speed);
			//acceleration.y = acceleration.y + (-speed);
		}
		if (key == SDL_SCANCODE_S)
		{
			velocity.y = clamp(velocity.y + (speed), -max_speed, max_speed);
		}
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