// JORGE DUART MARZO
// - rlyeh, public domain


#include "ENGINE.h"


//mario.palomino@ext.live.u-tad.com


bool Engine::Init() 
{ 
	m_screen = tigrWindow(m_iWidthScreen, m_iHeightScreen, "ENGINE", 0);
	m_isRunning = true; 
	if (!m_screen) return false;

	m_isRunning = true;
	return true; 
}

bool Engine::Input()
{
	return false;
}

bool Engine::Quit()
{ 
	tigrFree(m_screen);
	m_screen = nullptr;
	return true; 
}

bool Engine::isRunning()
{ 
	m_isRunning = !tigrClosed(m_screen);
	return m_isRunning; 
}

void Engine::Clear() const
{
	tigrClear(m_screen, tigrRGB(0,0,0));
	
}

void Engine::UpdateTIGR() const
{
	tigrUpdate(m_screen);
}

void Engine::Log(std::string text) const
{
	puts(text.c_str());
}

void Engine::Print(std::string text, int x, int y) const
{
	tigrPrint(m_screen, tfont, x, y, tigrRGB(0xff, 0xff, 0xff), text.c_str());
}

//----Time

double Engine::time_ms()
{
	static double t = 0;
	t += tigrTime();
	return t;
}

void Engine::wait(float ms)
{
	float last = static_cast<float>(time_ms());
	float time = 0.f;
	while (time < ms)
	{
		float now = static_cast<float>(time_ms());
		float delta = now - last;
		last = now;
		time += delta * 1000.f;
	}
}







