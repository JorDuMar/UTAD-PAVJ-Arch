#include "circleCollider.h"


CircleCollider::CircleCollider(Vec2 circlePos, float circleRadius) 
{
	m_vCirclePos = circlePos;
	m_fCircleRadius = circleRadius;
}

Vec2 CircleCollider::getCirclePos() const
{
	return m_vCirclePos;
}

float CircleCollider::getCircleRadius() const
{
	return m_fCircleRadius;
}

void CircleCollider::setCirclePos(Vec2 _vPos)
{
	m_vCirclePos = _vPos;
}
void CircleCollider::setCircleRadius(float _fRadius)
{
	m_fCircleRadius = _fRadius;
}

bool CircleCollider::collides(const Collider& other) const
{
	return (&other)->collides(getCirclePos(), getCircleRadius());
}

bool CircleCollider::collides(const Vec2& circlePos, float circleRadius) const
{

	return checkCircleCircle(circlePos, circleRadius, getCirclePos(), getCircleRadius());
}

bool CircleCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
	
	return checkCircleRect(getCirclePos(), getCircleRadius(), rectPos, rectSize);
}

bool CircleCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
	return checkCirclePixels(getCirclePos(), getCircleRadius(), pixelsPos, pixelsSize, pixels);
}