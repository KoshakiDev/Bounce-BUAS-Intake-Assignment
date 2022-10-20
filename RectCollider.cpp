#include <math.h>
#include "RectCollider.h"
using namespace std;

/*
Ray casting
A shooting game has typically many very fast, very small objects: bullets. 
Bullet collisions are better checked with ray casting. 
A ray is cast from the bullet’s current position to the bullet’s position of the next frame. 
This way no collisions are missed.

The ray casting approach can also be used for bigger objects if we cast a ray from the object center point to 
the future center point. 
We can get better results if we place more sample points in the object and shoot several rays. 
But this approach is not appropriate to test for collision of two moving objects 
because it is unlikely that rays of one object hit the rays of the other objects. 
The ray casting method is good for the bullet vs. slow object scenario.



void RectCollider::Draw(Surface* screen)
{
	int x1 = prevPointOnRect.x;
	int y1 = prevPointOnRect.y;
	screen->ApproximateCircle(x1, y1, 8, 1 * 255 * 255);
}

Vector2D RectCollider::GetPointOnRect(CircleCollider* other)
{
	Vector2D topLeft = GetTopLeftCorner();
	Vector2D topRight = GetTopRightCorner();
	Vector2D bottomLeft = GetBottomLeftCorner();
	Vector2D bottomRight = GetBottomRightCorner();
	Vector2D pointOnRect = Vector2D(
		clamp(other->GetTransform()->GetPosition().x + other->GetRadius(), topLeft.x, topRight.x),
		clamp(other->GetTransform()->GetPosition().y + other->GetRadius(), topLeft.y, bottomLeft.y)
	);
	curPointOnRect = pointOnRect;
	return pointOnRect;
}

Vector2D RectCollider::GetDistanceFromCircle(CircleCollider* other)
{
	Vector2D pointOnRect = GetPointOnRect(other);
	
	Vector2D distance = other->GetTransform()->GetPosition() + Vector2D(other->GetRadius(), other->GetRadius()) - pointOnRect;
	return distance;
}

bool RectCollider::IsCircleColliding(CircleCollider* other)
{
	Vector2D distance = GetDistanceFromCircle(other);
	
	if (distance.sqrLentgh() <= other->GetRadius() * other->GetRadius()) {
		return true;
	}
	return false;
}

bool RectCollider::IsRectColliding(RectCollider* other)
{
	Vector2D topLeft_1 = GetTopLeftCorner();
	Vector2D topRight_1 = GetTopRightCorner();
	Vector2D bottomLeft_1 = GetBottomLeftCorner();
	Vector2D bottomRight_1 = GetBottomRightCorner();
	
	Vector2D topLeft_2 = other->GetTopLeftCorner();
	Vector2D topRight_2 = other->GetTopRightCorner();
	Vector2D bottomLeft_2 = other->GetBottomLeftCorner();
	Vector2D bottomRight_2 = other->GetBottomRightCorner();

	if (
		topLeft_1.x < topRight_2.x &&
		topRight_1.x > topLeft_2.x &&
		topLeft_1.y <  bottomLeft_2.y &&
		bottomLeft_1.y > topLeft_2.y
		)
		return true;

	return false;
}
*/