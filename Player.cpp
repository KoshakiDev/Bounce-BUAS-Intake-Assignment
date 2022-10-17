#include "Player.h"

Sprite theSprite(new Surface("assets/ball.png"), 1);

void Player::Tick(float deltatime)
{
	clamp(velocity.x, -m_speed_cap, m_speed_cap);
	clamp(velocity.y, -m_speed_cap, m_speed_cap);
	if(abs(velocity.x) > 1.0 || abs(velocity.y) > 1.0)
		printf("Current Velocity exceeded: %f %f \n", velocity.x, velocity.y);
	GetPrevTransform()->SetTransform(GetTransform()->GetPosition());
	KinematicBody::Tick(deltatime);
}

void Player::ChangeTrajectory(vec2 collision_direction)
{

	vec2 pointOnRect = m_circle_collider.GetTransform()->GetPosition() + vec2(m_circle_collider.GetRadius(), m_circle_collider.GetRadius()) - collision_direction;
	float r = m_circle_collider.GetRadius();
	float prev_center_x = GetPrevTransform()->GetPosition().x + r;
	float prev_center_y = GetPrevTransform()->GetPosition().y + r;

	float cur_center_x = GetTransform()->GetPosition().x + r;
	float cur_center_y = GetTransform()->GetPosition().y + r;

	float new_x = 0;
	float new_y = 0;

	float t = 0;

	float sign = 1;

	if ((collision_direction.x == 0 && collision_direction.y != 0) || (collision_direction.x == 0 && collision_direction.y == 0 && prev_center_x == cur_center_x))// Solve for y
	{
		//printf("ENTERED SOLVE FOR Y \n");
		if (collision_direction.sqrLentgh() == 0)
		{
			if (signbit(velocity.y))
			{
				sign = 1;
			}
			else
			{
				sign = -1;
			}
			velocity.y = -velocity.y;
		}
		else
		{
			if (signbit(collision_direction.y))
			{
				sign = 1;
				velocity.y = -velocity.y;
			}
			else
			{
				sign = -1;
				velocity.y = -velocity.y;
			}
		}
		t = returnNewTrajectory(pointOnRect.y, r, sign, cur_center_y, prev_center_y);

	}
	else 
	if ((collision_direction.y == 0 && collision_direction.x != 0) || (collision_direction.x == 0 && collision_direction.y == 0 && prev_center_y == cur_center_y)) // Solve for x
	{
		//printf("ENTERED SOLVE FOR X \n");
		if(collision_direction.sqrLentgh() == 0)
		{
			if (signbit(velocity.x))
			{
				sign = 1;
				velocity.y = -velocity.y;
			}
			else
			{
				sign = -1;
				velocity.x = -velocity.x;
			}
		}
		else
		{
			if (signbit(collision_direction.x))
			{
				sign = 1;
				velocity.y = -velocity.y;
			}
			else
			{
				sign = -1;
				velocity.x = -velocity.x;
			}
		}
		t = returnNewTrajectory(pointOnRect.x, r, sign, cur_center_x, prev_center_x);
		
	}
	printf("%f \n", sign);
	new_y = t * prev_center_y + (1 - t) * cur_center_y;
	new_x = t * prev_center_x + (1 - t) * cur_center_x;
	
	/*
	printf("Point on Rect: %f %f \n", pointOnRect.x, pointOnRect.y);

	printf("Previous  CENTER    Position: %f %f \n", prev_center_x, prev_center_y);
	printf("Current   CENTER    Position: %f %f \n", cur_center_x, cur_center_y);
	printf("Corrected TRANSFORM Position: %f %f \n", new_x, new_y);
	/**/

	GetPrevTransform()->SetTransform(GetTransform()->GetPosition());
	GetTransform()->SetTransform(vec2(new_x - r, new_y - r));

	velocity *= 0.9;

	//KinematicBody::ChangeTrajectory(collision_direction);

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
	if (key == SDL_SCANCODE_E)
	{
		velocity = vec2(0, 0);
		GetTransform()->SetTransform(vec2(120, 120));
	}
	/*
	Remember that Y is flipped
	*/
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
	
}