#include "game.h"
#include "surface.h"
#include "Transform.h"
#include "RectCollider.h"

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
		// For testing purposes, set the rect collider here
		RectCollider* GetRectCollider() 
		{ 
			return &m_rect_collider; 
		}
		CircleCollider* GetCircleCollider()
		{
			return &m_circle_collider;	
		}
		
		Transform* GetTransform() { return &m_transform; }

		virtual void setRect(float width, float height) { m_rect_collider = RectCollider(width, height, &m_transform); }
		virtual void setRadius(float radius) 
		{ 
			is_circle = true;
			m_circle_collider = CircleCollider(radius, &m_transform); 
		}


		void updateCollider() 
		{ 
			if(is_circle)
				m_circle_collider.GetTransform()->SetTransform(m_transform.GetPosition());
			else
				m_rect_collider.GetTransform()->SetTransform(m_transform.GetPosition()); 
		}


	protected:
		Transform m_transform;
		// for the sake of testing, we will have circle and rectangle colliders here, these will be removed
		RectCollider m_rect_collider;
		CircleCollider m_circle_collider;
		bool is_circle = false;
		//vec2 m_velocity = vec2();
};