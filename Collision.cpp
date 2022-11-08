#include "Components.h"

bool Collision::Check(
	Shape* shape_1,
	Shape* shape_2,
	Vector2D& penetration_normal,
	float& penetration_depth
)
{
	if (shape_1->type == t_rectangle && shape_2->type == t_rectangle)
	{
		return CheckRectangleRectangle(shape_1, shape_2, penetration_normal, penetration_depth);
	}
	if (shape_1->type == t_circle && shape_2->type == t_circle)
	{
		return CheckCircleCircle(shape_1, shape_2, penetration_normal, penetration_depth);
	}
	if ((shape_1->type == t_circle && shape_2->type == t_rectangle) || (shape_2->type == t_circle && shape_1->type == t_rectangle))
	{
		return CheckCircleRectangle(shape_1, shape_2, penetration_normal, penetration_depth);
	}
	return false;
}

bool Collision::CheckCircleRectangle(
	Shape* circle,
	Shape* rectangle,
	Vector2D& penetration_normal,
	float& penetration_depth
)
{
	if (circle->type == t_rectangle && rectangle->type == t_circle)
	{
		swap(circle, rectangle);
	}
	Vector2D topLeft = rectangle->ptransformComponent->position;
	Vector2D topRight = rectangle->ptransformComponent->position + Vector2D(rectangle->params["width"], 0);
	Vector2D bottomLeft = rectangle->ptransformComponent->position + Vector2D(0, rectangle->params["height"]);
	Vector2D bottomRight = rectangle->ptransformComponent->position + Vector2D(rectangle->params["width"], rectangle->params["height"]);

	Vector2D pointOnRect = Vector2D(
		Clamp(circle->ptransformComponent->position.x, topLeft.x, topRight.x),
		Clamp(circle->ptransformComponent->position.y, topLeft.y, bottomLeft.y)
	);

	Vector2D intersection_vector = circle->ptransformComponent->position - pointOnRect;

	if (intersection_vector.sqrLentgh() < circle->params["radius"] * circle->params["radius"])
	{
		penetration_normal = intersection_vector.normalized();
		penetration_depth = circle->params["radius"] - intersection_vector.length();
		return true;
	}
	return false;
}

bool Collision::CheckCircleCircle(
	Shape* circle_1,
	Shape* circle_2,
	Vector2D& penetration_normal,
	float& penetration_depth
)
{
	Vector2D intersection_vector = circle_1->ptransformComponent->position - circle_2->ptransformComponent->position;

	float radius_sum = circle_1->params["radius"] + circle_2->params["radius"];

	if (intersection_vector.sqrLentgh() < radius_sum * radius_sum)
	{
		penetration_normal = intersection_vector.normalized();
		penetration_depth = radius_sum - intersection_vector.length();
		return true;
	}
	return false;
}

bool Collision::CheckRectangleRectangle(
	Shape* rectangle_1,
	Shape* rectangle_2,
	Vector2D& penetration_normal,
	float& penetration_depth
)
{
	Vector2D topLeft_1 = rectangle_1->ptransformComponent->position;
	Vector2D topRight_1 = rectangle_1->ptransformComponent->position + Vector2D(rectangle_1->params["width"], 0);
	Vector2D bottomLeft_1 = rectangle_1->ptransformComponent->position + Vector2D(0, rectangle_1->params["height"]);
	Vector2D bottomRight_1 = rectangle_1->ptransformComponent->position + Vector2D(rectangle_1->params["width"], rectangle_1->params["height"]);

	Vector2D topLeft_2 = rectangle_2->ptransformComponent->position;
	Vector2D topRight_2 = rectangle_2->ptransformComponent->position + Vector2D(rectangle_2->params["width"], 0);
	Vector2D bottomLeft_2 = rectangle_2->ptransformComponent->position + Vector2D(0, rectangle_2->params["height"]);
	Vector2D bottomRight_2 = rectangle_2->ptransformComponent->position + Vector2D(rectangle_2->params["width"], rectangle_2->params["height"]);

	if (
		topLeft_1.x < topRight_2.x &&
		topRight_1.x > topLeft_2.x &&
		topLeft_1.y <  bottomLeft_2.y &&
		bottomLeft_1.y > topLeft_2.y
		)
	{
		//nothing happens here to penetration variables
		//penetration_normal = intersection_vector.normalized();
		//penetration_depth = radius_sum - intersection_vector.length();
		return true;
	}
	return false;
}