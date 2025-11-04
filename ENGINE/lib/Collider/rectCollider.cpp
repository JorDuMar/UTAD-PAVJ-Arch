#include "rectCollider.h"
#include <stdio.h>

RectCollider::RectCollider(Vec2 rectPos, Vec2 rectSize)
{
	m_vRectPos = rectPos;
	m_vRectSize = rectSize;
}

Vec2 RectCollider::getRectPos() const
{
	return m_vRectPos;
}
Vec2 RectCollider::getRectSize() const
{
	return m_vRectSize;
}
void RectCollider::setRectPos(Vec2 newPos)
{
	m_vRectPos = newPos;
}
void RectCollider::setRectSize(Vec2 newSize)
{
	m_vRectSize = newSize;
}

bool RectCollider::collides(const Collider& other) const
{
	return (&other)->collides(getRectPos(), getRectSize());
}
bool RectCollider::collides(const Vec2& circlePos, float circleRadius) const
{
	return checkCircleRect(circlePos, circleRadius, getRectPos(), getRectSize());
}
bool RectCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
	return checkRectRect(rectPos, rectSize, getRectPos(), getRectSize());
}
bool RectCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
	/*printf("INI X PIXEL: %f, INI Y PIXEL: %f \n", pixelsPos.m_x + pixelsSize.m_x / 2.f, pixelsPos.m_y + pixelsSize.m_y/2.f);
	printf("POS X RECT: %f, POS Y RECT: %f \n", m_vRectPos.m_x, m_vRectPos.m_y);*/
	return checkPixelsRect(pixelsPos, pixelsSize, pixels, getRectPos(), getRectSize());
}