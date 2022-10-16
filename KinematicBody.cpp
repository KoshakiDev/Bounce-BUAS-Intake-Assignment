#include "KinematicBody.h"
#include "Vec.h"
#define GRAVITY 1
#define FRICTION 0.9


void KinematicBody::Tick(float deltatime)
{
	//acceleration = vec2(0, GRAVITY);
	velocity = velocity + acceleration * deltatime;
	vec2 position = GetTransform()->GetPosition();
	position = position + velocity * deltatime;
	GetTransform()->SetTransform(position);
}

void KinematicBody::ChangeTrajectory(vec2 collision_direction)
{
	//printf("Collision direction: %f, %f \n", collision_direction.x, collision_direction.y);
	//printf("===========\n");
	printf("Velocity before: %f %f \n", velocity.x, velocity.y);

	vec2 normal_direction = vec2(-collision_direction.y, collision_direction.x);
	
	normal_direction = normal_direction.normalized();
	//printf("Normal direction: %f, %f \n", normal_direction.x, normal_direction.y);

	//vec2 normal_velocity = velocity.normalized();
	if (normal_direction.y == 0)
	{
		velocity.y = -velocity.y;
	}
	else if (normal_direction.x == 0)
	{
		velocity.x = -velocity.x;
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
	velocity *= 0.5;
	printf("Velocity after: %f %f \n", velocity.x, velocity.y);
}