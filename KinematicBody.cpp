#include "KinematicBody.h"
#define GRAVITY 9.81
#define FRICTION 0.9


void KinematicBody::Tick(float deltatime)
{
	velocity = velocity + acceleration * deltatime;
	vec2 position = GetTransform()->GetPosition();
	position = position + velocity * deltatime;
	GetTransform()->SetTransform(position);
}