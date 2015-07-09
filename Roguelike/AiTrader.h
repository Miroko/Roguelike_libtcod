#pragma once
#include "CreatureAi.h"
#include "AiModuleCombat.h"

class AreaHouse;
class AiTrader : public CreatureAi
{
public:
	enum State{
		COMBAT,
		IN_HOUSE
	};
	State currentState;

	AreaHouse *houseIn;

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

	AiTrader() : CreatureAi(){};
};

