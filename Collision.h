#pragma once
#include "Components.h"

/*
This checks collision with primitives (point, line segment, circle, rectangle)
Check function is a double dispatch. 
We get 2 arbitrary shapes, we must figure out their types and use the correct function
*/




class Collision
{	
public:
	static void Check(Shape shape_1, Shape shape_2) {}

	static bool CheckCircleRectangle(Shape* circle, Shape* rectangle, Vector2D& penetration_normal, float& penetration_depth)
	{
		Vector2D topLeft = rectangle->position;
		Vector2D topRight = rectangle->position + Vector2D(rectangle->params["width"], 0);
		Vector2D bottomLeft = rectangle->position + Vector2D(0, rectangle->params["height"]);
		Vector2D bottomRight = rectangle->position + Vector2D(rectangle->params["width"], rectangle->params["height"]);
		
		Vector2D pointOnRect = Vector2D(
			Clamp(circle->position.x, topLeft.x, topRight.x),
			Clamp(circle->position.y, topLeft.y, bottomLeft.y)
		);

		Vector2D intersection_vector = circle->position - pointOnRect;
		
		if (intersection_vector.sqrLentgh() < circle->params["radius"] * circle->params["radius"])
		{
			penetration_normal = intersection_vector.normalized();
			penetration_depth = circle->params["radius"] - intersection_vector.length();
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
	
	

	static bool clipLine(int dimension, Shape* rectangle, Vector2D& v0, Vector2D& v1, float& f_low, float& f_high)
	{
		float f_dim_low;
		float f_dim_high;
		
		if (dimension == 0)
		{
			f_dim_low = (rectangle->position.x - v0.x) / (v1.x - v0.x);
			f_dim_high = ((rectangle->position.x + rectangle->params["width"]) - v0.x) / (v1.x - v0.x);
		}
		else if (dimension == 1)
		{
			f_dim_low = (rectangle->position.y - v0.y) / (v1.y - v0.y);
			f_dim_high = ((rectangle->position.y + rectangle->params["height"]) - v0.y) / (v1.y - v0.y);
		}

		// If this dimension's high is less than the low we got then we definitely missed. http://youtu.be/USjbg5QXk3g?t=7m16s
		if (f_dim_high < f_low)
			return false;

		// Likewise if the low is less than the high.
		if (f_dim_low > f_high)
			return false;

		// Add the clip from this dimension to the previous results http://youtu.be/USjbg5QXk3g?t=5m32s
		f_low = max(f_dim_low, f_low);
		f_high = min(f_dim_high, f_high);

		if (f_low > f_high)
			return false;

		return true;
 
	}

	static bool CheckRectangleLineSegment(
		Shape* rectangle, 
		Vector2D& v0, 
		Vector2D& v1, 
		Vector2D& intersection, 
		float& flFraction
	)
	{
		float f_low = 0;
		float f_high = 1;
		if (!clipLine(0, rectangle, v0, v1, f_low, f_high))
			return false;
		if (!clipLine(1, rectangle, v0, v1, f_low, f_high))
			return false;

		Vector2D b = v1 - v0;
		intersection = v0 + b * f_low;
		flFraction = f_low;
		return true;
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

	static void ChangeTrajectory(Object& player, Shape* rectangle, Object& test_point)
	{
		float r = player.getComponent<ShapeComponent>().pShape->params["radius"];
		Vector2D prev = player.getComponent<PrevTransformComponent>().position;
		Vector2D curr = player.getComponent<TransformComponent>().position;
		Vector2D output = Vector2D(-1, -1);

		float t = 0;

		float sign = 1;

		//###########

		float tan_angle = (curr.y - prev.y) / (curr.x - prev.y);
		float angle = atan(tan_angle);
		Vector2D prev_with_radius = Vector2D(prev.x - r * cos(angle), prev.y - r * sin(angle));
		Vector2D curr_with_radius = Vector2D(curr.x + r * cos(angle), curr.y + r * sin(angle));



		/*
		cout << "=============" << endl;
		cout << "Prev center: " << prev.x << " " << prev.y << endl;
		cout << "Curr center: " << curr.x << " " << curr.y << endl;

		cout << "Prev with radius: " << prev_with_radius.x << " " << prev_with_radius.y << endl;
		cout << "Curr with radius: " << curr_with_radius.x << " " << curr_with_radius.y << endl;
		/**/

		Vector2D intersection;
		float flFraction;

		if (CheckRectangleLineSegment(
			rectangle,
			prev_with_radius,
			curr_with_radius,
			intersection,
			flFraction
		))
		{
			intersection.x = float(ceil(intersection.x));
			intersection.y = float(ceil(intersection.y));

			test_point.getComponent<TransformComponent>().position.x = float(ceil(intersection.x));
			test_point.getComponent<TransformComponent>().position.y = float(ceil(intersection.y));
			//cout << "=============" << endl;
			//test_point.getComponent<TransformComponent>().position = intersection;
			//cout << rectangle->position << " " << rectangle->params["width"] << " " << rectangle->params["height"];
			//cout << intersection << endl;

			if (intersection.x == 0 && intersection.y != 0)// The side is Left-Right
			{
				//printf("ENTERED SOLVE FOR X \n");
				sign = returnSign(curr.x - prev.x);
				t = returnNewTrajectory(intersection.y, r, sign, curr.x, prev.x);
				player.getComponent<KinematicsComponent>().velocity.x *= (-1);

			}
			else if (intersection.y == 0 && intersection.x != 0) // The side is Up-Down
			{
				//printf("ENTERED SOLVE FOR Y \n");
				sign = returnSign(curr.y - prev.y);
				t = returnNewTrajectory(intersection.x, r, sign, curr.y, prev.y);
				player.getComponent<KinematicsComponent>().velocity.y *= (-1);
			}
		}
		else
			cout << "not detected" << endl;

		output.y = t * prev.y + (1 - t) * curr.y;
		output.x = t * prev.x + (1 - t) * curr.x;

		player.getComponent<TransformComponent>().position = output;
		player.getComponent<KinematicsComponent>().velocity *= 0.1;
	}

	static float returnNewTrajectory(float side, float radius, float sign, float cur_center, float prev_center)
	{
		if (prev_center == cur_center)
			printf("WARNING: DIVISION BY ZERO \n");
		return (side + (radius) * sign - cur_center) / (prev_center - cur_center);
	}
	static float returnSign(float value)
	{
		float sign = 0.0;
		if (signbit(value))
		{
			sign = 1.0;
		}
		else
		{
			sign = -1.0;
		}
		return sign;
	}
};
