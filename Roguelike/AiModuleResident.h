#pragma once
#include "AiModule.h"

class AreaDen;
class Bed;
class AiModuleResident : public AiModule
{
private:
	void wanderInsideResidence(AreaDen &residence);
	void sleep(Bed &bed);

public:
	enum State{
		SLEEPING,
		GO_SLEEP,
		WANDER
	};
	State currentState = WANDER;

	AreaDen *residence;
	Bed *bed;

	void AiModule::run();

	AiModuleResident() : AiModule(){};
};

