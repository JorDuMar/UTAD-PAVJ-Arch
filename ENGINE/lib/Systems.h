#pragma once
#include "Components.h"

class Vec2;
class CircleCollider;
class Tigr;

class Systems
{
public:
	void updateInputs(Tigr* _screen, float _deltaTime);
	void updatePhysics(float dt, int widthScreen, int heightScreen);
	void updateCollisions();
	void updateRender(Tigr* screen);

	int playerxs = 0;
};
