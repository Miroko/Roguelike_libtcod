#pragma once
#include "Dialog.h"
#include "TradeContainer.h"
#include <memory>

class QuestPhase;
class Quest
{
private:
	std::vector<std::shared_ptr<QuestPhase>> phases;
	std::shared_ptr<QuestPhase> village;
	std::shared_ptr<QuestPhase> currentPhase;

public:
	std::string name;

	std::shared_ptr<QuestPhase> const &getCurrentPhase();
	void setCurrentPhase(std::shared_ptr<QuestPhase> phase);

	std::shared_ptr<QuestPhase> const &getVillage();

	Quest(std::string name, std::vector<std::shared_ptr<QuestPhase>> phases) :
		name(name), phases(phases), village(phases.at(0)){};
};