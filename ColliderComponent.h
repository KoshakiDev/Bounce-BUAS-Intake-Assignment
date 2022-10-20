#pragma once
#include "Components.h"

class ColliderComponent : public Component
{
public:
	
	string tag;
	TransformComponent* ptransformComponent;
	ShapeComponent* pShapeComponent;

	void Init()
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

};