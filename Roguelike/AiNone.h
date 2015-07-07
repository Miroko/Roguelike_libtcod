#pragma once
#include "CreatureAi.h"

class AiNone : public CreatureAi
{
public:;
	void update();

	std::shared_ptr<CreatureAi> CreatureAi::copy();

	AiNone() : CreatureAi(){};
};

