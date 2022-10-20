#include "KinematicBody.h"

#define GRAVITY 0.5
#define FRICTION 0.9

int counter = 0;

void KinematicBody::Tick(float delta)
{
	GameObject::Tick(delta);
	getComponent<KinematicsComponent>().acceleration = Vector2D(0, 0);	
	getComponent<TransformComponent>().position = getComponent<TransformComponent>().position + getComponent<KinematicsComponent>().velocity * delta;
}

void KinematicBody::Draw(Surface* screen) 
{
	GameObject::Draw(screen);
}