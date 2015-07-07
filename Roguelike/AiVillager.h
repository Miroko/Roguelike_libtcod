#pragma once
#include "CreatureAi.h"
#include "AiModuleCombat.h"

class AiVillager : public CreatureAi
{
public:
	enum State{
		VISIT_HOUSE,
		WANDER,
		COMBAT
	};
	State currentState;

	AiModuleCombat combatModule;

	void onTakeDamage(DynamicObject &attacker);
	void onCreatureInFov(Creature &, int distance);
	void onOperatableInFov(OperatableObject &operatable, int distance);
	void nextToDestination(Point2D &location);
	void onPathBlocked(Point2D &location);
	void onPathEnd(Point2D &location);

	void initAi(Creature &owner, Area &area);
	void update();

	std::shared_ptr<CreatureAi> CreatureAi::copy();

	AiVillager() : CreatureAi(){};
};

