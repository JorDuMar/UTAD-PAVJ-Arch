// JORGE DUART MARZO
// - rlyeh, public domain
#pragma once

#include "resource.h"
#include "tigr.h"
#include <stdio.h>
#include "framework.h"
#include <string>
#include <sstream>
#include "ecs.hh"
#include "pugixml/pugixml.hpp"

class Engine
{

public:

	//Initialize engine creating a window. Return true if the window has been created, false otherwise.
	bool Init();

	bool Input();

	//Free tigrWindow memory.
	bool Quit();

	//Return true if the window hasn't been closed and the engine is running, false otherwise.
	bool isRunning();

	//Clears the screen with 0,0,0
	void Clear() const;

	void UpdateTIGR() const;

	//Creates Logs
	void Log(std::string text) const;

	//Print text in the screen, in coordinates x,y
	void Print(std::string text, int x = 0, int y = 0) const;

	//Return the time elapsed since this function was first called
	double time_ms();

	//Makes the engine wait with a loop 
	void wait(float ms);

	template<typename T>
	std::string toString(const T& t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}

	bool m_isRunning = false;
	Tigr* m_screen = nullptr;
	int m_iWidthScreen = 320;
	int m_iHeightScreen = 240;

};
