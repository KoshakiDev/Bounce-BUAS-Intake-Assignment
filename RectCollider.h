#pragma once
#include "Transform.h"
#include "CircleCollider.h"
#include <algorithm>

/*
NOTE: 
Rectangle's x and y positions are relative to the top left corner.
This is because Surface is programmed to draw Sprites from the position of the top left corner

*/

class RectCollider
{
public:
	RectCollider() = default;

	float clamp(float value, float min, float max)
	{
		if (value <= min) return min;
		if (value >= max) return max;
		return value;
	}

	RectCollider(float width, float height, Transform* transform)
	{
		//m_radius = radius;
		m_width = width;
		m_height = height;
		//m_transform->Transform(position);

		m_transform = transform;
		//m_transform->Translate(position); //may have errors due to m_transform being null
	}

	inline Transform* GetTransform() { return m_transform; }
	
	// Return each corner from the rectangle
	inline vec2 GetTopLeftCorner() 
	{ 
		vec2 corner = m_transform->GetPosition();
		return corner;
	}
	
	inline vec2 GetTopRightCorner() 
	{ 
		vec2 corner = m_transform->GetPosition();
		corner = corner + vec2(m_width, 0.0);
		return corner; 
	}
	inline vec2 GetBottomLeftCorner() 
	{
		vec2 corner = m_transform->GetPosition();
		corner = corner + vec2(0.0, m_height);
		return corner;
	}
	inline vec2 GetBottomRightCorner() 
	{
		vec2 corner = m_transform->GetPosition();
		corner = corner + vec2(m_width, m_height);
		return corner;
	}

	
	bool IsCircleColliding(CircleCollider* other);
	bool IsRectColliding(RectCollider* other);

private:
	Transform* m_transform = nullptr;

	//float m_radius = 1;
	float m_width = 0;
	float m_height = 0;

};

