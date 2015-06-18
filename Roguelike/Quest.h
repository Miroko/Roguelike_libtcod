#pragma once
#include "QuestPhase.h"
#include "Dialog.h"
#include <memory>
class Quest
{
public:
	std::string name;

	std::shared_ptr<QuestPhase> currentPhase = nullptr;

	virtual std::shared_ptr<QuestPhase> getNextPhase() = 0;
	virtual std::shared_ptr<QuestPhase> getVillage() = 0;
	virtual std::shared_ptr<Dialog> getDialog(std::shared_ptr<DynamicObject> &owner);
	
	Quest(std::string name) : name(name){};
};