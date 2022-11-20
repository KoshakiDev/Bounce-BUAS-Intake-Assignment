#include "ObjectComponentSystem.h"


// Here's the definition of `Entity::addToGroup`:
void Object::addGroup(Group mGroup) noexcept
{
	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}