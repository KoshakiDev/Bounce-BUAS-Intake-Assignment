#pragma once
#include "Vec.h"

/*
NOTE: This code was borrowed from Snow Wars

We can also include rotation, scale, etc, but is that needed?

This is essentially our Node2D?
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

