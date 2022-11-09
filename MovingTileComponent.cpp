#include "Components.h"

void MovingTileComponent::Init()
{
		if (!owner->hasComponent<TransformComponent>())
		{
			owner->addComponent<TransformComponent>();
		}
		ptransformComponent = &owner->getComponent<TransformComponent>();
}

void MovingTileComponent::Tick(float delta)
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