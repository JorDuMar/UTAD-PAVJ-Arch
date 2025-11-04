#pragma once

#include <math.h>

struct Vec2 
{
	float m_x;
	float m_y;

	Vec2(float x, float y);
	Vec2();

	Vec2 operator+(const Vec2& other) const;
	Vec2 operator+(float other) const;
	Vec2 operator-(const Vec2& other) const;
	Vec2 operator-(float other) const;
	Vec2 operator*(const Vec2& other) const;
	Vec2 operator*(float other) const;
	Vec2 operator/(const Vec2& other) const;
	Vec2 operator/(float other) const;

	Vec2 absolute() const;
	float length() const;
	Vec2 normalise() const;
	float dot(const Vec2& other) const;

	float angle(const Vec2& other) const;
	float distance(const Vec2& other) const;
};

float clamp(float num, float low, float high);