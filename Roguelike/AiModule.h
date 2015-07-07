#pragma once

class Creature;
class CreatureAi;
class AiModule
{
public:
	CreatureAi *owner;

	virtual void run() = 0;
	virtual void init(CreatureAi &owner);

	AiModule(){};
};

