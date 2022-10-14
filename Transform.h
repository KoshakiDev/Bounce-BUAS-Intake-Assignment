#pragma once
#include "Vec.h"

/*
NOTE: This code was borrowed from Snow Wars

Transform contains the 2D position vector.
Every other object in the game #includes this header.

Initially I wanted to include rotation, but then I realized that it would be incompatible with Surface. 
Surface does not have a built in understanding of rotation. 
This would mean that I have to drastically modify the given template

*/

class Transform
{
public:

	Transform() = default;

	Transform(vec2 position) { m_position = position; }

	vec2& GetPosition() { return m_position; }
	inline void Translate(vec2 direction) { m_position += direction; }
	inline void SetTransform(vec2 new_position) { m_position = new_position; }


protected:
	vec2 m_position;
};

