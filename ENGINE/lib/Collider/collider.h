#pragma once
#include <cstdint>
#include "mathUtils.h"
#include "collisionUtils.h"

class Collider 
{
public:
	virtual bool collides(const Collider& other) const = 0;
	virtual bool collides(const Vec2& circlePos, float circleRadius) const = 0;
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const = 0;
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const = 0;

	virtual ~Collider() {};

};