#include "Components.h"

void KinematicsComponent::Tick(float delta)
{
	// Activates friction
	if (abs(velocity.x) > 0)
	{
		if (velocity.x < 0)
		{
			velocity.x = Clamp(velocity.x - acceleration.x * delta, -max_speed, float(0.0));
		}
		if (velocity.x > 0)
		{
			velocity.x = Clamp(velocity.x + acceleration.x * delta, float(0.0), max_speed);
		}
	}
	// Activates gravity
	velocity.y = Clamp(velocity.y + acceleration.y * delta, -max_speed, max_speed);

	ptransformComponent->position = ptransformComponent->position + velocity * delta;
}