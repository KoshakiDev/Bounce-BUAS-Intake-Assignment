#include <math.h>
#include "RectCollider.h" //POSSIBLE SELF-REF
using namespace std;


bool RectCollider::IsCircleColliding(CircleCollider* other)
{
	vec2 topLeft = GetTopLeftCorner();
	vec2 topRight = GetTopRightCorner();
	vec2 bottomLeft = GetBottomLeftCorner();
	vec2 bottomRight = GetBottomRightCorner();
	vec2 pointOnRect = vec2(
		clamp(other->GetTrueCenter()->GetPosition().x, topLeft.x, topRight.x), 
		clamp(other->GetTrueCenter()->GetPosition().y, topLeft.y, bottomLeft.y)
	);

	vec2 distance = other->GetTrueCenter()->GetPosition() - pointOnRect;

	//float distanceX = other->GetTransform()->GetPosition().x - pointOnRect.x;
	//float distanceY = other->GetTransform()->GetPosition().y - pointOnRect.y;
	
	//float radiusSquared = m_radius + other->m_radius;
	
	printf("R Position: %f, %f \n", pointOnRect.x, pointOnRect.y);

	printf("O Position: %f, %f \n", other->GetTrueCenter()->GetPosition().x, other->GetTrueCenter()->GetPosition().y);
	printf("Distance: %f, Radius %f \n", distance.length(), other->GetRadius());

	if (distance.length() < other->GetRadius())
		return true;

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