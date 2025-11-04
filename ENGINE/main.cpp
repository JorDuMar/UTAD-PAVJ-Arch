// JORGE DUART MARZO

#include "ENGINE.h"
#include "LUA/LUA.h"
#include "iostream"
#include "LUA/minilua.h"
#include "sol/sol.hpp"
#include "Components.h"
#include "Systems.h"
#include "EntityManager.h"
#include "stdlib.h"
#include "Pang.h"

int main()
{
	Engine* engine = new Engine();
	if (engine->Init())
	{
		Systems* sys = new Systems();
		Pang* pangGame = new Pang(engine);
		pangGame->LoadBestScore("./data/GameData.xml");

		//Background
		Tigr* backdrop;
		backdrop = tigrBitmap(engine->m_screen->w, engine->m_screen->h);
		tigrClear(backdrop, tigrRGB(80, 180, 255));
		tigrFill(backdrop, 0, 200, 320, 40, tigrRGB(60, 120, 60));
		tigrFill(backdrop, 0, 200, 320, 3, tigrRGB(0, 0, 0));
		tigrLine(backdrop, 0, 201, 320, 201, tigrRGB(255, 255, 255));

		tigrSetPostFX(engine->m_screen, 1, 1, 1, 2.0f);

		while (engine->isRunning())
		{
			static double last = 0;
			double now = engine->time_ms();
			float deltaTime = static_cast<float>(now - last);
			last = now;
			float fps = 1.f / (deltaTime + !deltaTime);
			engine->wait(1000 / 60.f);

			if (!pangGame->isPaused())
			{
				//PLAYER INPUT
				sys->updateInputs(engine->m_screen, deltaTime);

				//PHYSICS
				sys->updatePhysics(deltaTime, engine->m_iWidthScreen, engine->m_iHeightScreen);

				//COLLIDERS
				sys->updateCollisions();

				//LOGIC
				pangGame->GameLogic();

				//RENDER
				tigrBlit(engine->m_screen, backdrop, 0, 0, 0, 0, backdrop->w, backdrop->h);
				sys->updateRender(engine->m_screen);

				engine->Print((engine->toString(pangGame->gameMinutes) + "m : " 
					+ engine->toString(pangGame->gameSeconds) + "s"));

				engine->Print(("High Score: " + engine->toString(pangGame->bestMinutes) + "m : " 
					+ engine->toString(pangGame->bestSeconds) + "s"), 0, 20);
			}
			else
			{
				pangGame->StartGame();
			}

			engine->UpdateTIGR();
		}

		engine->Quit();
		pangGame->SaveBestScore("./data/GameData.xml");
	
		delete pangGame;
		delete sys;
		tigrFree(backdrop);
	}
	delete engine;
}
