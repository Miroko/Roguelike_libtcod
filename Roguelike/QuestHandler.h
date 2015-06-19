#pragma once
#include "Quest.h"
class QuestHandler
{
public:
	std::shared_ptr<Quest> currentQuest;

	void setCurrentQuest(std::shared_ptr<Quest> quest);
	void generateNextPhase();
	void toVillage();
	void update();

	QuestHandler(){};
};

