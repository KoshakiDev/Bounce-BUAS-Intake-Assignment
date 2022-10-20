#pragma once

/*
WARNING: THIS WILL BE DELETED, IS REPLACED BY COLLIDER COMPONENT + SHAPE COMPONENT


#include "Transform.h"
#include "CircleCollider.h"
#include <algorithm>



class RectCollider
{
public:
	RectCollider() = default;

	string tag;

	RectCollider(float width, float height, Transform* transform)
	{
		m_width = width;
		m_height = height;
		m_transform = transform;
	}

	inline Transform* GetTransform() { return m_transform; }
	// new stuff
	// Return each corner from the rectangle
	inline Vector2D GetTopLeftCorner() 
	{ 
		Vector2D corner = m_transform->GetPosition();
		return corner;
	}
	
	inline Vector2D GetTopRightCorner() 
	{ 
		Vector2D corner = m_transform->GetPosition();
		corner = corner + Vector2D(m_width, 0.0);
		return corner; 
	}
	inline Vector2D GetBottomLeftCorner() 
	{
		Vector2D corner = m_transform->GetPosition();
		corner = corner + Vector2D(0.0, m_height);
		return corner;
	}
	inline Vector2D GetBottomRightCorner() 
	{
		Vector2D corner = m_transform->GetPosition();
		corner = corner + Vector2D(m_width, m_height);
		return corner;
	}
	//TESTING PURPOSES DRAW
	virtual void Draw(Surface* screen);

	Vector2D checkIfPointInRect(Vector2D point) 
	{
		if (GetTopLeftCorner().x < point.x && point.x < GetTopRightCorner().x && GetTopLeftCorner().y < point.y && point.y < GetBottomLeftCorner().y)
		{
			point = prevPointOnRect;
			cout << "WARNING: Previous point was used " << prevPointOnRect.x << ' ' << prevPointOnRect.y << endl;
		}
		return point;
	}

	Vector2D FindSideDirection(Vector2D point) 
	{
		Vector2D direction = Vector2D(0, 0);
		cout << "========" << endl;
		cout << "Point on/in rectangle "<< point.x << ' ' << point.y << endl;	

		if (GetTopLeftCorner().x < point.x && point.x < GetTopRightCorner().x)
		{
			//Either top side or bottom side
			if (point.y == GetTopRightCorner().y)
			{
				//it is a top side
				direction = GetTopRightCorner() - GetTopLeftCorner();
				cout << "Top side was chosen: " << direction.x << " " << direction.y << endl;

			}
			else
			{
				//it is a bottom side
				direction = GetBottomRightCorner() - GetBottomLeftCorner();
				cout << "Bottom side was chosen: " << direction.x << " " << direction.y << endl;
			}
		}
		else if (GetTopLeftCorner().y < point.y && point.y < GetBottomLeftCorner().y)
		{
			//Either right side or left side
			if (point.x == GetTopRightCorner().x)
			{
				//it is a right side
				direction =  GetBottomRightCorner() - GetTopRightCorner();
				cout << "Right side was chosen: " << direction.x << " " << direction.y << endl;
			}
			else
			{
				//it is the left side
				direction = GetBottomLeftCorner() - GetTopLeftCorner();
				cout << "Left side was chosen: " << direction.x << " " << direction.y << endl;
			}
		}
		else
		{
			//corner case, we will return either top or bottom side; temp solution
			printf("Corner case: ");
			if (point.y == GetTopRightCorner().y)
			{
				//it is a top side
				direction = GetTopRightCorner() - GetTopLeftCorner();
				cout << "Top side was chosen: " << direction.x << " " << direction.y << endl;
			}
			else
			{
				//it is a bottom side
				direction = GetBottomRightCorner() - GetBottomLeftCorner();
				cout << "Bottom side was chosen: " << direction.x << " " << direction.y << endl;
			}
		}
		return direction;
	}

	void updatePrevPointOnRect()
	{
		prevPointOnRect = curPointOnRect;
		curPointOnRect = Vector2D(0, 0);
	}

	Vector2D GetPointOnRect(CircleCollider* other);
	Vector2D GetDistanceFromCircle(CircleCollider* other);
	bool IsCircleColliding(CircleCollider* other);
	bool IsRectColliding(RectCollider* other);

private:
	Transform* m_transform = nullptr;
	float m_width = 0;
	float m_height = 0;

	Vector2D prevPointOnRect = Vector2D(0, 0);
	Vector2D curPointOnRect = Vector2D(0, 0);
};

*/