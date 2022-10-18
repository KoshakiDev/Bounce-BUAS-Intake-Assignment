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
*/


void RectCollider::Draw(Surface* screen)
{
	int x1 = prevPointOnRect.x;
	int y1 = prevPointOnRect.y;
	screen->ApproximateCircle(x1, y1, 8, 1 * 255 * 255);
}

vec2 RectCollider::GetPointOnRect(CircleCollider* other)
{
	vec2 topLeft = GetTopLeftCorner();
	vec2 topRight = GetTopRightCorner();
	vec2 bottomLeft = GetBottomLeftCorner();
	vec2 bottomRight = GetBottomRightCorner();
	vec2 pointOnRect = vec2(
		clamp(other->GetTransform()->GetPosition().x + other->GetRadius(), topLeft.x, topRight.x),
		clamp(other->GetTransform()->GetPosition().y + other->GetRadius(), topLeft.y, bottomLeft.y)
	);
	curPointOnRect = pointOnRect;
	return pointOnRect;
}

vec2 RectCollider::GetDistanceFromCircle(CircleCollider* other)
{
	vec2 pointOnRect = GetPointOnRect(other);
	
	vec2 distance = other->GetTransform()->GetPosition() + vec2(other->GetRadius(), other->GetRadius()) - pointOnRect;
	return distance;
}

bool RectCollider::IsCircleColliding(CircleCollider* other)
{
	vec2 distance = GetDistanceFromCircle(other);
	
	if (distance.sqrLentgh() <= other->GetRadius() * other->GetRadius()) {
		return true;
	}
	return false;
}

bool RectCollider::IsRectColliding(RectCollider* other)
{
	vec2 topLeft_1 = GetTopLeftCorner();
	vec2 topRight_1 = GetTopRightCorner();
	vec2 bottomLeft_1 = GetBottomLeftCorner();
	vec2 bottomRight_1 = GetBottomRightCorner();
	
	vec2 topLeft_2 = other->GetTopLeftCorner();
	vec2 topRight_2 = other->GetTopRightCorner();
	vec2 bottomLeft_2 = other->GetBottomLeftCorner();
	vec2 bottomRight_2 = other->GetBottomRightCorner();

	if (
		topLeft_1.x < topRight_2.x &&
		topRight_1.x > topLeft_2.x &&
		topLeft_1.y <  bottomLeft_2.y &&
		bottomLeft_1.y > topLeft_2.y
		)
		return true;

	return false;
}