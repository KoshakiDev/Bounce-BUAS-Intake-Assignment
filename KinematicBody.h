#pragma once
#include "GameObject.h"

class KinematicBody : public GameObject
{
public:
	KinematicBody() = default;

	KinematicBody(vec2 position) : GameObject(position) 
	{
		velocity = vec2(0, 0);
		acceleration = vec2(0, 0);
	}
	~KinematicBody() {}
	virtual void Tick(float deltatime) override;
	virtual void Draw(Surface* screen) {}
	virtual void Input(int key) {}

	vec2 GetVelocity() { return velocity; }
	vec2 GetAcceleration() { return acceleration; }
	void SetVelocity(vec2 new_velocity) { velocity = new_velocity; }
	void SetAcceleration(vec2 new_acceleration) { acceleration = new_acceleration; }


protected:
	vec2 velocity;
	vec2 acceleration;
};