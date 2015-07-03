#pragma once
#include "CreatureAi.h"

class AiMonster : public CreatureAi
{
public:
	Creature *target;

	void onTakeDamage(DynamicObject &attacker);
	void onCreatureInFov(Creature &, int distance);
	void onOperatableInFov(OperatableObject &operatable, int distance);
	void onDestination(Point2D &location);
	void onPathBlocked(Point2D &location);
	void onPathEnd(Point2D &location);;

	void initAi(Creature &owner);
	void update();

	AiMonster() : CreatureAi(){}
};

