#pragma once
#include <math.h>
#include <iostream>

/*
THIS IS NOT IN USE ANYMORE, VECTOR2D WAS MOVED TO TEMPLATE.H

NOTE: This code was borrowed from Snow Wars, updated to print out vectors correctly based from "Lets Make Games"



struct Vector2D // adapted from https://github.com/dcow/RayTracer
{
	union { struct { float x, y; }; float cell[2]; };
	Vector2D() { x = 0; y = 0; }
	Vector2D(float v) : x(v), y(v) {}
	Vector2D(float x, float y) : x(x), y(y) {}
	Vector2D(int x, int y) : x((float)x), y((float)y) {}
	Vector2D operator - () const { return Vector2D(-x, -y); }
	Vector2D operator + (const Vector2D& addOperand) const { return Vector2D(x + addOperand.x, y + addOperand.y); }
	Vector2D operator - (const Vector2D& operand) const { return Vector2D(x - operand.x, y - operand.y); }
	Vector2D operator * (const Vector2D& operand) const { return Vector2D(x * operand.x, y * operand.y); }
	Vector2D operator * (float operand) const { return Vector2D(x * operand, y * operand); }
	void operator -= (const Vector2D& a) { x -= a.x; y -= a.y; }
	void operator += (const Vector2D& a) { x += a.x; y += a.y; }
	void operator *= (const Vector2D& a) { x *= a.x; y *= a.y; }
	void operator *= (float a) { x *= a; y *= a; }
	float& operator [] (const int idx) { return cell[idx]; }
	float length() { return sqrtf(x * x + y * y); }
	float sqrLentgh() { return x * x + y * y; }
	Vector2D normalized() { float r = 1.0f / length(); return Vector2D(x * r, y * r); }
	void normalize() { float r = 1.0f / length(); x *= r; y *= r; }
	static Vector2D normalize(Vector2D v) { return v.normalized(); }
	float dot(const Vector2D& operand) const { return x * operand.x + y * operand.y; }

	friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
	{
		stream << "(" << vec.x << ", " << vec.y << ")";
		return stream;
	}
	
};
*/