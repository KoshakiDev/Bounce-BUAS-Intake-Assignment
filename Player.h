#pragma once
#include "KinematicBody.h"


class Player : public KinematicBody
{
public:
	Player(Manager& mManager, Vector2D position, float speed, float max_speed, ShapeType type) : KinematicBody(mManager, position, speed, max_speed)
	{
		addComponent<ShapeComponent>(type);
		addComponent<ColliderComponent>();
	}
	~Player() {}

	void Tick(float delta) override;
	void Draw(Surface* screen) override;
	void Input(int key) override;
};
