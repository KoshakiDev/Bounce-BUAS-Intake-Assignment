#include "Components.h"

ShapeComponent::ShapeComponent(ShapeType type)
{
    ShapeComponent::pShape = Shape::Create(type);
}

void ShapeComponent::Init()
{
    if (!owner->hasComponent<TransformComponent>())
    {
        owner->addComponent<TransformComponent>();
    }
    ptransformComponent = &owner->getComponent<TransformComponent>();
    pShape->ptransformComponent = &owner->getComponent<TransformComponent>();
}