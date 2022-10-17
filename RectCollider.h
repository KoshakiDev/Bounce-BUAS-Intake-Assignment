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
		m_width = width;
		m_height = height;
		m_transform = transform;
	}

	inline Transform* GetTransform() { return m_transform; }
	// new stuff
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
	//TESTING PURPOSES DRAW
	virtual void Draw(Surface* screen);

	vec2 FindSideDirection(vec2 point) 
	{
		vec2 direction = vec2(0, 0);
		if (GetTopLeftCorner().x < point.x && point.x < GetTopRightCorner().x)
		{
			//Either top side or bottom side
			if (point.y == GetTopRightCorner().y)
			{
				//it is a top side
				direction = GetTopRightCorner() - GetTopLeftCorner();
			}
			else
			{
				//it is a bottom side
				direction = GetBottomRightCorner() - GetBottomLeftCorner();
			}
		}
		else if (GetTopLeftCorner().y < point.y && point.y < GetBottomLeftCorner().y)
		{
			//Either right side or left side
			if (point.x == GetTopRightCorner().x)
			{
				//it is a right side
				direction = GetTopRightCorner() - GetBottomRightCorner();
			}
			else
			{
				//it is the left side
				direction = GetTopLeftCorner() - GetBottomLeftCorner();
			}
		}
		else
		{
			//corner case, we will return either top or bottom side; temp solution
			printf("Corner case \n");
			if (point.y == GetTopRightCorner().y)
			{
				//it is a top side
				direction = GetTopRightCorner() - GetTopLeftCorner();
			}
			else
			{
				//it is a bottom side
				direction = GetBottomRightCorner() - GetBottomLeftCorner();
			}
		}
		return direction;
	}

	vec2 GetPointOnRect(CircleCollider* other);
	vec2 GetDistanceFromCircle(CircleCollider* other);
	bool IsCircleColliding(CircleCollider* other);
	bool IsRectColliding(RectCollider* other);

private:
	Transform* m_transform = nullptr;
	float m_width = 0;
	float m_height = 0;

	vec2 prevPointOnRect = vec2(0, 0);
};

