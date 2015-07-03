#pragma once
#include "CreatureAi.h"

class AiNone : public CreatureAi
{
public:
	void initAi(Creature &owner);
	void update();

	AiNone() : CreatureAi(){};
};

