#include "Systems.h"
#include "Collider/mathUtils.h"
#include "Collider/circleCollider.h"
#include "Collider/rectCollider.h"

#include "EntityManager.h"
#include "tigr.h"


void Systems::updateInputs(Tigr* _screen, float _deltaTime)
{
	
	for (auto& id : join<health, position>())
	{
		Vec2& playerPos = get<position>(id);
		if (tigrKeyHeld(_screen, TK_LEFT) || tigrKeyHeld(_screen, 'A'))
			playerxs -= 10;
		if (tigrKeyHeld(_screen, TK_RIGHT) || tigrKeyHeld(_screen, 'D'))
			playerxs += 10;

		// Apply simply physics.
		playerxs *= exp(-10.0f * _deltaTime);
		playerPos.m_x += _deltaTime * playerxs;

		// Apply collision.
		if (playerPos.m_x < 8) {
			playerPos.m_x = 8;
			playerxs = 0;
		}

		if (playerPos.m_x > _screen->w - 8) {
			playerPos.m_x = _screen->w - 8.0f;
			playerxs = 0;
		}

	}
	
}

void Systems::updatePhysics(float dt, int widthScreen, int heightScreen)
{
	for (auto& id : join<ia, velocity, position, sprite1>())
	{
		Vec2& pos = get<position>(id);
		Vec2& vel = get<velocity>(id);
		Tigr*& sprite = get<sprite1>(id);

		vel.m_y += 9.8f * dt;
		pos.m_x += vel.m_x * dt;
		pos.m_y += vel.m_y * dt;

		if (pos.m_y >= 200.f) //ground
		{
			pos.m_y = 200.f;
			vel.m_y = -50.f;
		}

		if (pos.m_x <= (0.f + sprite->w / 2.f) || pos.m_x >= (static_cast<float>(widthScreen) - sprite->w / 2.f))
		{
			vel.m_x *= -1.f;
		}

	}
}

void Systems::updateCollisions()
{
	for (auto& id : join<position, collider>())
	{
		Vec2& pos = get<position>(id);
		sCollider coll = get<collider>(id);
		CollisionType myType = coll.type;
		if (myType == COLLISION_CIRCLE)
		{
			static_cast<CircleCollider*>(coll.collider)->setCirclePos(Vec2(pos.m_x, pos.m_y));
		}
		else if (myType == COLLISION_RECT)
		{
			static_cast<RectCollider*>(coll.collider)->setRectPos(Vec2(pos.m_x, pos.m_y));
		}
	}
}

void Systems::updateRender(Tigr* screen)
{
	for (auto& id : join<position, sprite1>())
	{
		Tigr*& sprite = get<sprite1>(id);
		Vec2& pos = get<position>(id);
		tigrBlitAlpha(screen, sprite, (int)pos.m_x - sprite->w / 2, (int)pos.m_y - sprite->h, 0, 0, sprite->w,
			sprite->h, 1.0f);
	}
}
