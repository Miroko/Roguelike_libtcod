#pragma once
#include "AiModule.h"

class DynamicObject;
class AiModuleCombat : public AiModule
{
private:
	void pursueAndAttack(DynamicObject &target);

public:
	DynamicObject *target = nullptr;

	void AiModule::run();

	AiModuleCombat() : AiModule(){};
};

