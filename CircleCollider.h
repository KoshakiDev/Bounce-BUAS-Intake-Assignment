#pragma once
#include "Transform.h"
#include <iostream>

/*
* NOTE: This was borrowed from Snow Wars
*/

class CircleCollider
{
public:
	CircleCollider() = default;

	CircleCollider(float radius, Transform* transform)
	{
		m_radius = radius;
		m_transform = transform;
	}

	inline Transform* GetTransform() { return m_transform; }

	bool IsColliding(CircleCollider* other);

private:
	Transform* m_transform = nullptr;
	float m_radius = 1;
};

