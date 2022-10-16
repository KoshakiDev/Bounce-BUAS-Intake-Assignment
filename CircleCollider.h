#pragma once
#include "Transform.h"
#include <iostream>
#include "GameObject.h"

/*
NOTE: This was borrowed from Snow Wars
This is used by the player kinematic body.

The circle has a "transform" which is located in the top left corner
The circle also has a "true center", which is kept in mind when calculating

This is because of the way Surface was built.
*/

class CircleCollider : public GameObject
{
public:
	CircleCollider() = default;

	CircleCollider(float radius, Transform* transform)
	{
		m_radius = radius;
		m_transform = transform;
	}

	inline Transform* GetTransform() { return m_transform; }
	
	inline float GetRadius() { return m_radius; }

	bool IsCircleColliding(CircleCollider* other);

private:
	Transform* m_transform = nullptr;
	float m_radius = 1;
};

