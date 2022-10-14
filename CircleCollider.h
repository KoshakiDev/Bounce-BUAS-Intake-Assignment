#pragma once
#include "Transform.h"
//#include "RectCollider.h" //NOTE: This line may bug because of circular referencing, RectColider has ref to CircleCollider
#include <iostream>

/*
NOTE: This was borrowed from Snow Wars
This is used by the player kinematic body.
The circle collider's transform is not located in its "center", it is located on its top left corner.
This is because of the way Surface was built.
The "center" used 


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

	//bool IsRectColliding(RectCollider* other);
	//NOTE: Create IsCollidingWithRect

private:
	Transform* m_transform = nullptr;
	float m_radius = 1;
	Transform* m_true_center = nullptr;
};

