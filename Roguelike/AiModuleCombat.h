#pragma once
#include "AiModule.h"

class Creature;
class AiModuleCombat : public AiModule
{
public:
	Creature *target;

	void AiModule::run();

	AiModuleCombat() : AiModule(){};
};

