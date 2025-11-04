#pragma once
#include "collider.h"

class RectCollider : public Collider
{
public:
	RectCollider(Vec2 rectPos, Vec2 rectSize);
	Vec2 getRectPos() const;
	Vec2 getRectSize() const;
	void setRectPos(Vec2 newPos);
	void setRectSize(Vec2 newSize);
	bool collides(const Collider& other) const;
	bool collides(const Vec2& circlePos, float circleRadius) const;
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
	bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;

private:
	Vec2 m_vRectPos;
	Vec2 m_vRectSize;
};