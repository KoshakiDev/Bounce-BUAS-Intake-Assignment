#pragma once
#include "Transform.h"
#include <iostream>

/*
NOTE: This was borrowed from Snow Wars
This is used by the player kinematic body.

The circle has a "transform" which is located in the top left corner
The circle also has a "true center" which is located in the circle's center

This is because of the way Surface was built.
*/

class CircleCollider
{
public:
	CircleCollider() = default;

	CircleCollider(float radius, Transform* transform)
	{
		m_radius = radius;
		m_transform = transform;
		m_true_center = transform;
		m_true_center->SetTransform(m_true_center->GetPosition() + vec2(radius, radius));
	}

	inline Transform* GetTransform() { return m_transform; }
	
	inline Transform* GetTrueCenter() { return m_true_center; }
	
	inline float GetRadius() { return m_radius; }

	bool IsCircleColliding(CircleCollider* other);

private:
	Transform* m_transform = nullptr;
	float m_radius = 1;
	Transform* m_true_center = nullptr;
};

