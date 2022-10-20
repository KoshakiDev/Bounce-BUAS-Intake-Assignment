#pragma once
#include "Components.h"
#include <typeinfo>

/*
This checks collision with primitives (point, line segment, circle, rectangle)
Check function is a double dispatch. 
We get 2 arbitrary shapes, we must figure out their types and use the correct function
*/

class Collision
{
public:

	static void Check(Shape shape_1, Shape shape_2)
	{
		
	}

	static bool CheckCircleRectangle(const Circle circle, const Rectangle rectangle)
	{

	}
	static bool CheckCircleCircle(const Circle circle_1, const Circle circle_2)
	{

	}
	static bool CheckCirclePoint(const Circle circle, const Point point)
	{

	}
	static bool CheckCircleLineSegment(const Circle circle, const LineSegment lineSegment)
	{

	}
	static bool CheckRectangleRectangle(const Rectangle rectangle_1, const Rectangle rectangle_2)
	{

	}
	static bool CheckRectanglePoint(const Rectangle rectangle, const Point point)
	{

	}
	static bool CheckRectangleLineSegment(const Rectangle rectangle, const LineSegment lineSegment)
	{

	}
	static bool CheckPointPoint(const Point point_1, const Point point_2)
	{

	}
	static bool CheckPointLineSegment(const Point point, const LineSegment lineSegment)
	{

	}
	static bool CheckLineSegmentLineSegment(const LineSegment lineSegment_1, const LineSegment lineSegment_2)
	{

	}
	/*
	void Player::ChangeTrajectory(Vector2D side, Vector2D pointOnRect)
	{
		float r = m_circle_collider.GetRadius();

		float prev_center_x = GetPrevTransform()->GetPosition().x + r;
		float prev_center_y = GetPrevTransform()->GetPosition().y + r;

		float cur_center_x = GetTransform()->GetPosition().x + r;
		float cur_center_y = GetTransform()->GetPosition().y + r;

		float new_x = 0;
		float new_y = 0;

		float t = 0;

		float sign = 1;

		if (side.x == 0 && side.y != 0)// The side is Left-Right
		{
			//printf("ENTERED SOLVE FOR X \n");
			sign = returnSign(cur_center_x - prev_center_x);
			t = returnNewTrajectory(side.y, r, sign, cur_center_x, prev_center_x);
			velocity.x = -velocity.x;
		}
		else if (side.y == 0 && side.x != 0) // The side is Up-Down
		{
			//printf("ENTERED SOLVE FOR Y \n");
			sign = returnSign(cur_center_y - prev_center_y);
			t = returnNewTrajectory(side.x, r, sign, cur_center_y, prev_center_y);
			velocity.y = -velocity.y;
		}

		new_y = t * prev_center_y + (1 - t) * cur_center_y;
		new_x = t * prev_center_x + (1 - t) * cur_center_x;


		/*
		printf("Side         : %f %f \n", side.x, side.y);
		printf("Point on Rect: %f %f \n", pointOnRect.x, pointOnRect.y);

		printf("  t  Value: %f \n", t);
		printf("Sign Value: %f \n", sign);
		printf("Previous  CENTER    Position: %f %f \n", prev_center_x, prev_center_y);
		printf("Current   CENTER    Position: %f %f \n", cur_center_x, cur_center_y);
		printf("Corrected TRANSFORM Position: %f %f \n", new_x, new_y);
		/*

		GetPrevTransform()->SetTransform(GetTransform()->GetPosition());
		GetTransform()->SetTransform(Vector2D(new_x - r, new_y - r));

		velocity *= 0.9;

		//KinematicBody::ChangeTrajectory(collision_direction);

	}

	float returnNewTrajectory(float side, float radius, float sign, float cur_center, float prev_center)
	{
		if (prev_center == cur_center)
			printf("WARNING: DIVISION BY ZERO \n");
		return (side + (radius) * sign - cur_center) / (prev_center - cur_center);
	}
	/**/
};