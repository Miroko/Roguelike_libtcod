#pragma once
#include "AiModule.h"

class AreaHouse;
class Bed;
class AiModuleResident : public AiModule
{
private:
	void wanderInsideResidence(AreaHouse &residence);
	void sleep(Bed &bed);

public:
	enum State{
		SLEEPING,
		GO_SLEEP,
		WANDER
	};
	State currentState = WANDER;

	AreaHouse *residence;
	Bed *bed;

	void AiModule::run();

	AiModuleResident() : AiModule(){};
};

