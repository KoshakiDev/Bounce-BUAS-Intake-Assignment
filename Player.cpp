#include "Player.h"


void Player::Tick(float deltatime)
{
	KinematicBody::Tick(deltatime);
	//printf("%f %f \n", velocity.x, velocity.y);
}

void Player::Draw(Surface* screen)
{
	int x1 = m_circle_collider.GetTrueCenter()->GetPosition().x;
	int y1 = m_circle_collider.GetTrueCenter()->GetPosition().y;
	screen->ApproximateCircle(x1, y1, m_circle_collider.GetRadius(), 255 * 255 * 255);
}

void Player::Input(int key)
{
	if (key == SDL_SCANCODE_D)
	{
		velocity += vec2(1, 0);
	}
	if (key == SDL_SCANCODE_A)
	{
		velocity -= vec2(1, 0);
	}
}