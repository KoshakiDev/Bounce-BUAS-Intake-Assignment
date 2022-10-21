#pragma once
#include "game.h"
#include "surface.h"
#include "Components.h"


/*
GameObject is the base class for Tile and KinematicBody. It has a 2D position (Transform) in form of a vector.

*/

class GameObject : public Object
{
	public:
		
		GameObject(Manager& mManager, Vector2D position) : Object(mManager)
		{
			addComponent<TransformComponent>(position);
		}
		~GameObject() {}
		
		virtual void Tick(float delta) 
		{
			Object::Tick(delta);
			cout << "i am working";
		}
		virtual void Draw(Surface* screen) 
		{
			Object::Draw(screen);
		}
		virtual void Input(int key) {}
};