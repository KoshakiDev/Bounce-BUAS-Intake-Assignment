#pragma once
#include "Components.h"

class ColliderComponent : public Component
{
public:
	
	string tag;
	TransformComponent* ptransformComponent;
	ShapeComponent* pShapeComponent;
	
	ColliderComponent(string t)
	{
		tag = t;
	}

	void Init() override
	{
		if (!owner->hasComponent<TransformComponent>())
		{
			owner->addComponent<TransformComponent>();
		}
		ptransformComponent = &owner->getComponent<TransformComponent>();
		if (!owner->hasComponent<ShapeComponent>())
		{
			//if the owner does not have a shape, we default to a rectangle
			owner->addComponent<ShapeComponent>(t_rectangle);
		}
		pShapeComponent = &owner->getComponent<ShapeComponent>();
	}

	void Tick(float delta)
	{
		
	}
};