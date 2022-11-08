#pragma once
#include "Components.h"

/*

Purpose:
- Check collisions between two shapes (circles and rectangles). 
- Double dispatch directs arbitrary shapes to use correct functions

Using the normal and the depth, it helps us:
- Move the object out in the correct direction and at correct distance
- Change velocity's trajectory

Note:
- Only the Cirlce-Rectangle collision check is used. 
  However, if needed, collisions between two rectangles and between two circles can be used.
*/

class Collision
{	
public:
	// Double-dispatch function
	static bool Check(
		Shape* shape_1,
		Shape* shape_2,
		Vector2D& penetration_normal,
		float& penetration_depth
	);

	static bool CheckCircleRectangle(
		Shape* circle,
		Shape* rectangle,
		Vector2D& penetration_normal,
		float& penetration_depth
	);
	
	static bool CheckCircleCircle(
		Shape* circle_1,
		Shape* circle_2,
		Vector2D& penetration_normal,
		float& penetration_depth
	);
	
	static bool CheckRectangleRectangle(
		Shape* rectangle_1,
		Shape* rectangle_2,
		Vector2D& penetration_normal,
		float& penetration_depth
	);
};
