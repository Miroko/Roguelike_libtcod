#pragma once
#include "CreatureAi.h"
#include "AiModuleCombat.h"

class AiMonster : public CreatureAi
{
public:
	Creature *target;
	AiModuleCombat combat;

	void onTakeDamage(DynamicObject &attacker);
	void onCreatureInFov(Creature &, int distance);
	void onOperatableInFov(OperatableObject &operatable, int distance);
	void nextToDestination(Point2D &location);
	void onPathBlocked(Point2D &location);
	void onPathEnd(Point2D &location);

	void initAi(Creature &owner, Area &area);

	void update();

	std::shared_ptr<CreatureAi> CreatureAi::copy();

	AiMonster() : CreatureAi(),
		combat(AiModuleCombat()){}
};

