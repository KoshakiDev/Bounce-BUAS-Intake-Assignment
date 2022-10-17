#pragma once
#include "KinematicBody.h"
#include "RectCollider.h"

class Player : public KinematicBody
{
public:
	Player(vec2 position) : KinematicBody(position) {}
	~Player() {}

	void Tick(float deltatime) override;
	void Draw(Surface* screen) override;
	void Input(int key) override;

	void ChangeTrajectory(vec2 collision_direction) override;
	
	float returnNewTrajectory(float pointOnRect, float radius, float sign, float cur_center, float prev_center)
	{
		return (pointOnRect + (radius) * sign - cur_center) / (prev_center - cur_center);
	}
	


	CircleCollider* GetCircleCollider()
	{
		return &m_circle_collider;
	}
	virtual void setRadius(float radius)
	{
		m_circle_collider = CircleCollider(radius, &m_transform);
	}

	Transform* GetPrevTransform() { return &m_prev_transform; }

protected:
	float m_speed_cap = 1.0;
	float m_speed = 0.5;
	CircleCollider m_circle_collider;
	Transform m_prev_transform;
};
