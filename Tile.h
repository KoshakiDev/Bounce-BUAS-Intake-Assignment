#pragma once
#include "GameObject.h"
#include "RectCollider.h"

class Tile : public GameObject
{
public:
	Tile(vec2 position) : GameObject(position) {}
	
	virtual void Tick(float deltatime) override;
	virtual void Draw(Surface* screen) override;
	virtual void Input(int key) {}

	virtual void setRect(float width, float height) 
	{
		m_rect_collider = RectCollider(width, height, &m_transform); 
	}

	RectCollider* GetRectCollider()
	{
		return &m_rect_collider;
	}
protected:
	RectCollider m_rect_collider;
	
};