#pragma once
#include "AiModule.h"
#include "Point2D.h"

class DynamicObject;
class AiModuleCombat : public AiModule
{
private:
	void pursueAndAttack(DynamicObject &target);
	void flee();

public:
	enum State{
		PURSUE,
		FLEE,
		WAIT,
	};
	State state = WAIT;

	Point2D fleeLocation = POINT_UNDEFINED;
	DynamicObject *target = nullptr;

	void AiModule::run();

	AiModuleCombat() : AiModule(){};
};

