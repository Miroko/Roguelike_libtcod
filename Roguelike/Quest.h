#pragma once
#include "Dialog.h"
#include "TradeContainer.h"
#include <memory>

class QuestPhase;
class Quest
{
public:
	std::string name;
	int currentPhaseIndex;
	std::vector<std::shared_ptr<QuestPhase>> phases;
	std::shared_ptr<QuestPhase> village;
	std::shared_ptr<QuestPhase> currentPhase;

	void setCurrentPhase(std::shared_ptr<QuestPhase> phase);
	std::shared_ptr<QuestPhase> const &getNextPhase();
	std::shared_ptr<QuestPhase> const &getCurrentPhase();
	std::shared_ptr<QuestPhase> const &getVillage();

	Quest(std::string name, std::vector<std::shared_ptr<QuestPhase>> phases) :
		name(name), phases(phases), village(phases.at(0)){};
};