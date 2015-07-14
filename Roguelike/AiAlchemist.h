#pragma once
#include "CreatureAi.h"
#include "AiModuleCombat.h"
#include "AiModuleResident.h"

class AlchemyTable;
class AiAlchemist : public CreatureAi
{
public:
	enum State{
		COMBAT,
		IN_HOUSE,
		USE_ALCHEMY_TABLE
	};
	State currentState;

	AiModuleCombat combatModule;
	AiModuleResident residentModule;
	AlchemyTable *alchemyTableUsing = nullptr;

	void onTakeDamage(DynamicObject &attacker);
	void onCreatureInFov(Creature &, int distance);
	void onOperatableInFov(OperatableObject &operatable, int distance);
	void nextToDestination(Point2D &location);
	void onPathBlocked(Point2D &location);
	void onPathEnd(Point2D &location);

	void initAi(Creature &owner, Area &area);
	void update();

	std::shared_ptr<CreatureAi> CreatureAi::copy();

	AiAlchemist() : CreatureAi(){};
};

