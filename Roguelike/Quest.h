#pragma once
#include "QuestPhase.h"
#include <memory>
class Quest
{
public:
	std::string name;

	std::shared_ptr<QuestPhase> currentPhase = nullptr;

	virtual std::shared_ptr<QuestPhase> getNextPhase() = 0;
	virtual std::shared_ptr<QuestPhase> getVillage() = 0;
	
	Quest(std::string name) : name(name){};
};