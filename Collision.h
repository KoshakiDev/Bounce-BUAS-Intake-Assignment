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
		if (shape_1.type == t_circle && shape_2.type == t_rectangle)
		{
			// I can't send shape_1 and shape_2 to the checker, it says that it can't convert Shape to Circle/Rect
			//CheckCircleRectangle(shape_1, shape_2);
		}
	}

	static bool CheckCircleRectangle(Circle circle, Rectangle rectangle)
	{
		Vector2D topLeft = rectangle.position;
		Vector2D topRight = rectangle.position + Vector2D(rectangle.params["width"], 0);
		Vector2D bottomLeft = rectangle.position + Vector2D(0, rectangle.params["height"]);
		Vector2D bottomRight = rectangle.position + Vector2D(rectangle.params["width"], rectangle.params["height"]);
		
		
		Vector2D pointOnRect = Vector2D(
			Clamp(circle.position.x, topLeft.x, topRight.x),
			Clamp(circle.position.y, topLeft.y, bottomLeft.y)
		);

		Vector2D distance = circle.position - pointOnRect;
		
		if (distance.sqrLentgh() <= circle.params["radius"] * circle.params["radius"])
		{
			return true;
		}
		return false;
	}
	static bool CheckCircleCircle(Circle circle_1, Circle circle_2)
	{
		float distanceX = circle_1.position.x - circle_2.position.x;
		float distanceY = circle_1.position.y - circle_2.position.y;
		float radiusSquared = circle_1.params["radius"] + circle_2.params["radius"];
		distanceX *= distanceX;
		distanceY *= distanceY;
		radiusSquared *= radiusSquared;

		if (distanceX + distanceY < radiusSquared)
			return true;

		return false;
	}
	static bool CheckCirclePoint(const Circle circle, const Point point)
	{

	}
	static bool CheckCircleLineSegment(const Circle circle, const LineSegment lineSegment)
	{

	}
	static bool CheckRectangleRectangle(Rectangle rectangle_1, Rectangle rectangle_2)
	{
		Vector2D topLeft_1 = rectangle_1.position;
		Vector2D topRight_1 = rectangle_1.position + Vector2D(rectangle_1.params["width"], 0);
		Vector2D bottomLeft_1 = rectangle_1.position + Vector2D(0, rectangle_1.params["height"]);
		Vector2D bottomRight_1 = rectangle_1.position + Vector2D(rectangle_1.params["width"], rectangle_1.params["height"]);

		Vector2D topLeft_2 = rectangle_2.position;
		Vector2D topRight_2 = rectangle_2.position + Vector2D(rectangle_2.params["width"], 0);
		Vector2D bottomLeft_2 = rectangle_2.position + Vector2D(0, rectangle_2.params["height"]);
		Vector2D bottomRight_2 = rectangle_2.position + Vector2D(rectangle_2.params["width"], rectangle_2.params["height"]);

		if (
			topLeft_1.x < topRight_2.x &&
			topRight_1.x > topLeft_2.x &&
			topLeft_1.y <  bottomLeft_2.y &&
			bottomLeft_1.y > topLeft_2.y
			)
			return true;

		return false;
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
	*/
};
