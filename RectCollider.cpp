#include <math.h>
#include "RectCollider.h"
using namespace std;


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
	prevPointOnRect = pointOnRect;
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
		//printf("Collided! Square Distance %f out of %f\n", distance.sqrLentgh(), other->GetRadius() * other->GetRadius());
		/*
		printf("===========\n");
		if (distance.sqrLentgh() == 0)
			printf("Collided! Uh oh! The distance is zero, we can't tell the direction!\n");
		else
			printf("Collided! Direction of Distance: %f %f\n", distance.x, distance.y);
		/**/
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