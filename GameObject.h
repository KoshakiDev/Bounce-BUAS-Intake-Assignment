#pragma once

#include "game.h"
#include "surface.h"
#include "Transform.h"

using namespace std;
using namespace Tmpl8;

/*
GameObject is the base class for Tile and KinematicBody. It has a 2D position (Transform) in form of a vector.

*/

class GameObject 
{
	public:
		GameObject() = default;
		/*
		NOTE: When creating a constructor, do not put a ";" at the end of it. 
		Putting one makes the constructor non-existent
		*/
		GameObject(vec2 position)
		{
			m_transform = Transform(position);
			m_instantiated = true;
		}
		~GameObject() {}

		virtual void Tick(float deltaTime) {}
		virtual void Draw(Surface* screen) {}
		virtual void Input(int key) {}

		Transform* GetTransform() { return &m_transform; }
		bool IsInstantiated() { return m_instantiated; }


	protected:
		Transform m_transform;
		bool m_instantiated = false;
};