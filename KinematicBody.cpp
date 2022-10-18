#include "KinematicBody.h"
#include "Vec.h"
#define GRAVITY 0.5
#define FRICTION 0.9

int counter = 0;

void KinematicBody::Tick(float deltatime)
{
	acceleration = vec2(0, 0);
	velocity.x = clamp(velocity.x + acceleration.x * deltatime, -m_speed_cap, m_speed_cap);
	velocity.y = clamp(velocity.y + acceleration.y * deltatime, -m_speed_cap, m_speed_cap);


	vec2 position = GetTransform()->GetPosition();
	position = position + velocity * deltatime;
	GetTransform()->SetTransform(position);
}
