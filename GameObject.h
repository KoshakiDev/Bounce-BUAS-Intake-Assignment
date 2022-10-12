#include "game.h"
#include "surface.h"
#include "Vec.h"
#include "Transform.h"
#include "CircleCollider.h"

using namespace std;
using namespace Tmpl8;



class GameObject {
	public:
		GameObject(vec2 position)
		{
			m_transform = Transform(position);
		};
		~GameObject();
		void Tick(float deltaTime);
		void Draw(Surface* screen);
		void Input(int key);
	protected:
		Transform m_transform;
		vec2 m_velocity = vec2();
};