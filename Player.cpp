#include "Player.h"


void Player::Tick(float delta)
{
	KinematicBody::Tick(delta);
	//GetPrevTransform()->SetTransform(GetTransform()->GetPosition());
}



void Player::Draw(Surface* screen)
{
	KinematicBody::Draw(screen);
}

void Player::Input(int key)
{
	/*
	if (key == SDL_SCANCODE_E)
	{
		velocity = Vector2D(0, 0);
		GetTransform()->SetTransform(Vector2D(120, 120));
	}
	/*
	Remember that Y is flipped
	
	if (key == SDL_SCANCODE_W)
	{
		velocity.y = clamp(velocity.y + (-m_speed), -m_speed_cap, m_speed_cap);
	}
	if (key == SDL_SCANCODE_S)
	{
		velocity.y = clamp(velocity.y + (m_speed), -m_speed_cap, m_speed_cap);
	}
	if (key == SDL_SCANCODE_D)
	{
		velocity.x = clamp(velocity.x + (m_speed), -m_speed_cap, m_speed_cap);
	}
	if (key == SDL_SCANCODE_A)
	{
		velocity.x = clamp(velocity.x + (-m_speed), -m_speed_cap, m_speed_cap);
	}
	clamp(velocity.x, -m_speed_cap, m_speed_cap);
	clamp(velocity.y, -m_speed_cap, m_speed_cap);
	*/
}