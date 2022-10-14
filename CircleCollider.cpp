#include <math.h>
#include "CircleCollider.h"

bool CircleCollider::IsCircleColliding(CircleCollider* other)
{
	float distanceX = other->GetTransform()->GetPosition().x - GetTransform()->GetPosition().x;
	float distanceY = other->GetTransform()->GetPosition().y - GetTransform()->GetPosition().y;
	float radiusSquared = m_radius + other->m_radius;
	distanceX *= distanceX;
	distanceY *= distanceY;
	radiusSquared *= radiusSquared;

	if (distanceX + distanceY < radiusSquared)
		return true;

	return false;
}
