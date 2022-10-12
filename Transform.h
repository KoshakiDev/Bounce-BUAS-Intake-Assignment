#pragma once
#include "Vec.h"

/*
NOTE: This code was borrowed from Snow Wars

Transform contains the 2D position vector and the rotation in radians.
Every other object in the game #includes this header.

*/

class Transform
{
public:

	Transform() = default;

	Transform(vec2 position) { m_position = position; }

	vec2& GetPosition() { return m_position; }
	inline void Translate(vec2 direction) { m_position += direction; }

protected:
	vec2 m_position;
};

