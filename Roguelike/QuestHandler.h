#pragma once
#include "Quest.h"
class QuestHandler
{
public:
	std::vector<std::shared_ptr<Quest>> quests;
	Quest *currentQuest;
	QuestPhase *currentPhase;

	void addQuest(Quest *quest);
	void setCurrentQuest(Quest *quest);
	void generateNextPhase();

	QuestHandler(){};
};

