#include "game.h"
#include "surface.h"
#include "Transform.h"

using namespace std;
using namespace Tmpl8;

/*
GameObject is the base class for Tile and KinematicBody. It has a 2D position (Transform) in form of a vector.

*/

class GameObject {
	public:
		GameObject(vec2 position)
		{
			m_transform = Transform(position);
		};
		~GameObject();
		virtual void Tick(float deltaTime);
		virtual void Draw(Surface* screen);
		virtual void Input(int key);
	protected:
		Transform m_transform;
		//vec2 m_velocity = vec2();
};