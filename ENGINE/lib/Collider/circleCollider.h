#pragma once
#include "collider.h"

class CircleCollider : public Collider 
{
public:
	CircleCollider(Vec2 circlePos, float circleRadius);
	Vec2 getCirclePos() const;
	float getCircleRadius() const;
	void setCirclePos(Vec2 newPos);
	void setCircleRadius(float newRadius);
	bool collides(const Collider& other) const;
	bool collides(const Vec2& circlePos, float circleRadius) const;
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
	bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;

private:
	Vec2 m_vCirclePos;
	float m_fCircleRadius;
};
