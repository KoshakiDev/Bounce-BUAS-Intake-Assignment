#include "PlayerComponent.h"

#define ROCK_COEFFICIENT 2
#define BALLOON_COEFFICIENT -0.1

void PlayerComponent::Init()
{
    ptransformComponent = &owner->getComponent<TransformComponent>();
    pShapeComponent = &owner->getComponent<ShapeComponent>();
    pKinematicsComponent = &owner->getComponent<KinematicsComponent>();
}

void PlayerComponent::MouseUp(int button)
{
}

void PlayerComponent::MouseDown(int button)
{
}

void PlayerComponent::MouseMove(int x, int y)
{
}

void PlayerComponent::KeyUp(int key)
{
    //Remember that Y is flipped
    if (key == SDL_SCANCODE_D)
    {
        pKinematicsComponent->velocity.x = clamp(
            pKinematicsComponent->velocity.x + (pKinematicsComponent->speed), 
            -pKinematicsComponent->max_speed, 
            pKinematicsComponent->max_speed);
    }
    if (key == SDL_SCANCODE_A)
    {
        pKinematicsComponent->velocity.x = clamp(
            pKinematicsComponent->velocity.x + (-pKinematicsComponent->speed), 
            -pKinematicsComponent->max_speed, 
            pKinematicsComponent->max_speed);
    }
    clamp(pKinematicsComponent->velocity.x, -pKinematicsComponent->max_speed, pKinematicsComponent->max_speed);
    clamp(pKinematicsComponent->velocity.y, -pKinematicsComponent->max_speed, pKinematicsComponent->max_speed);

    if (key == SDL_SCANCODE_J) //Balloon
    {
        pKinematicsComponent->acceleration = Vector2D(FRICTION, GRAVITY * BALLOON_COEFFICIENT);
        pKinematicsComponent->bounce_coefficient = 0.2;
        pShapeComponent->pShape->object_type = t_balloon;
    }
    if (key == SDL_SCANCODE_K) //Ball
    {
        pKinematicsComponent->acceleration = Vector2D(FRICTION, GRAVITY);
        pKinematicsComponent->bounce_coefficient = 0.99;
        pShapeComponent->pShape->object_type = t_ball;
    }
    if (key == SDL_SCANCODE_L) //Rock
    {
        pKinematicsComponent->acceleration = Vector2D(FRICTION, GRAVITY * ROCK_COEFFICIENT);
        pKinematicsComponent->bounce_coefficient = 0.0;
        pShapeComponent->pShape->object_type = t_rock;
    }
}

void PlayerComponent::KeyDown(int key)
{
}
