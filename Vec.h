#pragma once
#include <math.h>

/*
NOTE: This code was borrowed from Snow Wars
*/


struct vec2 // adapted from https://github.com/dcow/RayTracer
{
	union { struct { float x, y; }; float cell[2]; };
	vec2() { x = 0; y = 0; }
	vec2(float v) : x(v), y(v) {}
	vec2(float x, float y) : x(x), y(y) {}
	vec2(int x, int y) : x((float)x), y((float)y) {}
	vec2 operator - () const { return vec2(-x, -y); }
	vec2 operator + (const vec2& addOperand) const { return vec2(x + addOperand.x, y + addOperand.y); }
	vec2 operator - (const vec2& operand) const { return vec2(x - operand.x, y - operand.y); }
	vec2 operator * (const vec2& operand) const { return vec2(x * operand.x, y * operand.y); }
	vec2 operator * (float operand) const { return vec2(x * operand, y * operand); }
	void operator -= (const vec2& a) { x -= a.x; y -= a.y; }
	void operator += (const vec2& a) { x += a.x; y += a.y; }
	void operator *= (const vec2& a) { x *= a.x; y *= a.y; }
	void operator *= (float a) { x *= a; y *= a; }
	float& operator [] (const int idx) { return cell[idx]; }
	float length() { return sqrtf(x * x + y * y); }
	float sqrLentgh() { return x * x + y * y; }
	vec2 normalized() { float r = 1.0f / length(); return vec2(x * r, y * r); }
	void normalize() { float r = 1.0f / length(); x *= r; y *= r; }
	static vec2 normalize(vec2 v) { return v.normalized(); }
	float dot(const vec2& operand) const { return x * operand.x + y * operand.y; }
};

