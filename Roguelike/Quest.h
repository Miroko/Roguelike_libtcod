#pragma once
#include "QuestPhase.h"
#include "Random.h"
#include "vector"
#include "memory"
class Quest
{
public:
	std::shared_ptr<QuestPhase> currentPhase = nullptr;

	virtual std::shared_ptr<QuestPhase> getNextPhase() = 0;
	
	Quest(){};
};