#include "mathUtils.h"

const float fToDeg = 57.2957795;

Vec2::Vec2(float x, float y) 
{
	m_x = x;
	m_y = y;
}

Vec2::Vec2() 
{
	m_x = 0.0f;
	m_y = 0.0f;
}

Vec2 Vec2::operator+(const Vec2& other) const 
{
	float x = this->m_x + other.m_x;
	float y = this->m_y + other.m_y;
	return Vec2(x, y);
}

Vec2 Vec2::operator+(float other) const 
{
	float x = this->m_x + other;
	float y = this->m_y + other;
	return Vec2(x, y);
}

Vec2 Vec2::operator-(const Vec2& other) const 
{
	float x = this->m_x - other.m_x;
	float y = this->m_y - other.m_y;
	return Vec2(x, y);
}

Vec2 Vec2::operator-(float other) const 
{
	float x = this->m_x - other;
	float y = this->m_y - other;
	return Vec2(x, y);
}

Vec2 Vec2::operator*(const Vec2& other) const 
{
	float x = this->m_x * other.m_x;
	float y = this->m_y * other.m_y;
	return Vec2(x, y);
}

Vec2 Vec2::operator*(float other) const 
{
	float x = this->m_x * other;
	float y = this->m_y * other;
	return Vec2(x, y);
}

Vec2 Vec2::operator/(const Vec2& other) const 
{
	float x = this->m_x / other.m_x;
	float y = this->m_y / other.m_y;
	return Vec2(x, y);
}

Vec2 Vec2::operator/(float other) const 
{
	float x = this->m_x / other;
	float y = this->m_y / other;
	return Vec2(x, y);
}

Vec2 Vec2::absolute() const 
{
	float x = fabsf(this->m_x);
	float y = fabsf(this->m_y);
	return Vec2(x, y);

}

float Vec2::length() const
{
	return sqrtf(this->m_x * this->m_x + this->m_y * this->m_y);
}

Vec2 Vec2::normalise() const 
{
	float len = this->length();
	if (len == 0.0f) 
	{
		return Vec2(0.0f, 0.0f);
	}
	float x = this->m_x / len;
	float y = this->m_y / len;
	return Vec2(x, y);
}

float Vec2::dot(const Vec2& other) const 
{
	return this->m_x * other.m_x + this->m_y * other.m_y;
}

float Vec2::angle(const Vec2& other) const 
{
	 float res = fmod(atan2f(this->m_y - other.m_y, other.m_x - this->m_x) * fToDeg, 360);
	 if (res < 0) { res += 360.0f; }
	 return res;
}

float Vec2::distance(const Vec2& other) const 
{
	return sqrtf((other.m_y - this->m_y) * (other.m_y - this->m_y) + (other.m_x - this->m_x) * (other.m_x - this->m_x));
}

float clamp(float num, float low, float high)
{
	float res_ = num;
	if (num < low) { res_ = low; }
	if (num > high) { res_ = high; }
	return res_;
}