#pragma once
#include "GameObject.h"

class KinematicBody : public GameObject
{
public:
	KinematicBody() = default;

	KinematicBody(Manager& mManager, Vector2D position, float speed, float max_speed) : GameObject(mManager, position)
	{
		addComponent<KinematicsComponent>(speed, max_speed);
	}
	~KinematicBody() {}
	virtual void Tick(float delta) override;
	virtual void Draw(Surface* screen) override;
	virtual void Input(int key) {}
};