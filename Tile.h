#pragma once
#include "GameObject.h"

/*

class Tile : public GameObject
{
public:
	Tile(Vector2D position) : GameObject(position) {}
	
	virtual void Tick(float delta) override;
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

	//CRUTCH
	bool getReal() { return is_real; }
	void setReal() { is_real = true; }

	void setFake() { is_real = false; }

protected:
	RectCollider m_rect_collider;

	bool is_real = true;
};
*/