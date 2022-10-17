#include "KinematicBody.h"
#include "Vec.h"
#define GRAVITY 0.5
#define FRICTION 0.9

int counter = 0;

void KinematicBody::Tick(float deltatime)
{
	acceleration = vec2(0, 0.5);
	velocity = velocity + acceleration * deltatime;
	
	vec2 position = GetTransform()->GetPosition();
	position = position + velocity * deltatime;
	GetTransform()->SetTransform(position);
}

void KinematicBody::ChangeTrajectory(vec2 collision_direction)
{
	
	velocity *= 0.9;
}

//printf("Normal Velocity: %f, %f \n", normal_velocity.x, normal_velocity.y);
	/*
	float angle = acos((normal_velocity.x * normal_direction.x) + (normal_velocity.y * normal_direction.y));
	printf("%f \n", angle);
	float sine = sin(M_PI - angle);
	float cosine = cos(M_PI - angle);
	printf("cosine, sine: %f, %f \n", cosine, sine);

	vec2 new_velocity = vec2(0, 0);
	new_velocity.x = velocity.x * cosine - velocity.y * sine;
	new_velocity.y = velocity.x * sine + velocity.y * cosine;
	velocity = new_velocity;
	/**/
