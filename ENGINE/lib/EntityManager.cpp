#include "EntityManager.h"
#include "ecs.hh"
#include "Components.h"
#include "tigr.h"
#include "Collider/mathUtils.h"
#include "Collider/circleCollider.h"
#include "Collider/rectCollider.h"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
	if (m_iPlayer != -1)
	{
		del<position>(m_iPlayer);
		del<sprite1>(m_iPlayer);
		delete get<collider>(m_iPlayer).collider;
		del<collider>(m_iPlayer);
		del<velocity>(m_iPlayer);
		del<health>(m_iPlayer);
	}
	ResetGame();

}

int EntityManager::CreatePlayer()
{
	if (m_iPlayer == -1)
	{
		m_iPlayer = 1;
		add<position>(m_iPlayer) = Vec2(160, 200);
		add<sprite1>(m_iPlayer) = tigrLoadImage("./data/squinkle.png");
		add<health>(m_iPlayer) = 1;
		sCollider coll;
		coll.type = CollisionType::COLLISION_RECT;
		coll.collider = new RectCollider(Vec2(160, 200), Vec2(get<sprite1>(m_iPlayer)->w, get<sprite1>(m_iPlayer)->h));
		add<collider>(m_iPlayer) = coll;
	}
	return m_iPlayer;
}

int EntityManager::GetPlayer() const
{
  return m_iPlayer;
}

int EntityManager::GetCurrentNumEnemies() const
{
	return currentEnemies;
}

void EntityManager::CreateEnemy(int _x, int _y)
{
	unsigned int enemyId = entities + currentEnemies;
	float velX = static_cast<int>(rand() % 100 - 50);
	int randomSize = rand() % 2;
	int randomColor = rand() % 3;
	add<position>(enemyId) = Vec2(_x, _y);
	add<sprite1>(enemyId) = tigrLoadImage(spriteMatrix[randomSize][randomColor]);
	sCollider coll;
	coll.type = CollisionType::COLLISION_CIRCLE;
	coll.collider = new CircleCollider(Vec2(get<position>(enemyId).m_x, get<position>(enemyId).m_y),
		get<sprite1>(enemyId)->w / 2.f);
	add<collider>(enemyId) = coll;
	if (!get<ia>(enemyId))
	{
		add<ia>(enemyId) = new IA();
	}
	add<velocity>(enemyId) = Vec2(velX, 0.f);

	currentEnemies++;
}

void EntityManager::ResetGame()
{
	for (unsigned int i = entities; i < entities + currentEnemies; i++)
	{
		del<position>(i);
		tigrFree(get<sprite1>(i));
		del<sprite1>(i);
		delete get<collider>(i).collider;
		del<collider>(i);
		del<velocity>(i);
		delete get<ia>(i);
		del<ia>(i);
	}
	currentEnemies = 0;
}
