#pragma once
#include "ecs.hh"
#include "../ENGINE.h"

struct IA
{};

class CircleCollider;
class Vec2;
class Collider;

enum CollisionType {
	COLLISION_NONE,
	COLLISION_CIRCLE,
	COLLISION_RECT,
};

struct sCollider
{
	CollisionType type;
	Collider* collider;
};

//COMPONENTS
using position = component< Vec2, 'pos2' >;
using sprite1 = component<Tigr*, 'sprt'>;
using health = component<int, 'heal'>;
using collider = component<sCollider, 'coll'>; 
using velocity = component<Vec2, 'vel'>;
using ia = component<IA*, 'ia'>;