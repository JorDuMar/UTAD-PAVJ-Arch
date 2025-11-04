#include "Pang.h"
#include "ecs.hh"
#include "Components.h"
#include "Systems.h"
#include "EntityManager.h"
#include "ENGINE.h"
#include "Collider/circleCollider.h"
#include "pugixml/pugixml.hpp"

Pang::Pang(Engine* _eng)
{
  m_pEntManager = new EntityManager();
	m_iPlayerEntity = m_pEntManager->CreatePlayer();
	m_pEngine = _eng;
}

Pang::~Pang()
{
  if (m_pEntManager)
  {
    delete m_pEntManager;
  }
}

void Pang::StartGame()
{
	if (paused)
	{
		m_pEngine->Clear();
		m_pEngine->Print("PRESS SPACE TO START",
			(m_pEngine->m_iWidthScreen / 2) - 70, (m_pEngine->m_iHeightScreen / 2) - 10);
		if (tigrKeyHeld(m_pEngine->m_screen, TK_SPACE))
		{
			paused = false;
			totalTime = m_pEngine->time_ms();
			cooldown = false;
		}
	}
}

void Pang::GameLogic()
{
	if (!paused)
	{
		Collider* collPlayer = get<collider>(m_iPlayerEntity).collider;
		for (auto& id : join<ia, collider>())
		{
			Collider* collEnemy = get<collider>(id).collider;
			if (collPlayer && collEnemy && collPlayer->collides(*collEnemy))
			{
				//Delete enemies
				m_pEntManager->ResetGame();

				//Update best time
				if (gameSecs > bestTime)
				{
					bestTime = gameSecs;
				}
				totalTime += gameSecs;
				gameSecs = 0.;
				paused = true;
				break;
			}
		}

		if (!paused && static_cast<unsigned int>(gameSecs) % 5 == 0 && !cooldown)
		{
			m_pEntManager->CreateEnemy(m_pEngine->m_iWidthScreen / 2, 0);
			cooldown = true;
		}
		else if (!paused && static_cast<unsigned int>(gameSecs) % 5 != 0)
		{
			cooldown = false;
		}

		gameSecs = m_pEngine->time_ms() - totalTime;
		gameMinutes = static_cast<unsigned int>(gameSecs) / 60u;
		gameSeconds = static_cast<unsigned int>(gameSecs) % 60;

		bestMinutes = static_cast<unsigned int>(bestTime) / 60;
		bestSeconds = static_cast<unsigned int>(bestTime) % 60;
	}
}

bool Pang::LoadBestScore(const char* _filename)
{
	pugi::xml_document doc;
	if (!doc.load_file(_filename)) return false;

	pugi::xml_node highScoreNode = doc.child("GameData").child("HighScore");
	if (highScoreNode) {
		bestMinutes = highScoreNode.child("BestMinutes").text().as_int();
		bestSeconds = highScoreNode.child("BestSeconds").text().as_int();
		bestTime = static_cast<double>(bestSeconds) + static_cast<double>(bestMinutes * 60);
		return true;
	}
	return false;
}

bool Pang::SaveBestScore(const char* _filename) const
{
	pugi::xml_document doc;
	if (!doc.load_file(_filename)) return false;

	pugi::xml_node highScoreNode = doc.child("GameData").child("HighScore");
	if (!highScoreNode) return false;

	highScoreNode.child("BestMinutes").text().set(bestMinutes);
	highScoreNode.child("BestSeconds").text().set(bestSeconds);
	if (!doc.save_file(_filename)) return false;

	return true;
}

bool Pang::isPaused() const
{
	return paused;
}
