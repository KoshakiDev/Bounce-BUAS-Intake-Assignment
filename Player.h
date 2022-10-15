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


	CircleCollider* GetCircleCollider()
	{
		return &m_circle_collider;
	}
	virtual void setRadius(float radius)
	{
		m_circle_collider = CircleCollider(radius, &m_transform);
	}

protected:
	CircleCollider m_circle_collider;
};
