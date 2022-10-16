#include "Player.h"

Sprite theSprite(new Surface("assets/ball.png"), 1);

void Player::Tick(float deltatime)
{
	KinematicBody::Tick(deltatime);
	//printf("%f %f \n", velocity.x, velocity.y);
}

void Player::Draw(Surface* screen)
{
	/*
	theSprite.DrawScaled(
		GetTransform()->GetPosition().x,
		GetTransform()->GetPosition().y,
		m_circle_collider.GetRadius() * 2,
		m_circle_collider.GetRadius() * 2,
		screen
	);
	/**/
	int x1 = m_circle_collider.GetTransform()->GetPosition().x + m_circle_collider.GetRadius();
	int y1 = m_circle_collider.GetTransform()->GetPosition().y + m_circle_collider.GetRadius();
	screen->ApproximateCircle(x1, y1, m_circle_collider.GetRadius(), 255 * 255 * 255);
}

void Player::Input(int key)
{
	/*
	Remember that Y is flipped
	*/
	if (key == SDL_SCANCODE_W)
	{
		velocity += vec2(0, -1);
	}
	if (key == SDL_SCANCODE_D)
	{
		velocity += vec2(1, 0);
	}
	if (key == SDL_SCANCODE_A)
	{
		velocity -= vec2(1, 0);
	}
}