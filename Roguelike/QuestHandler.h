#pragma once
#include <vector>
#include <memory>

class Quest;
class QuestHandler
{
private:
	std::shared_ptr<Quest> currentQuest;

public:
	std::shared_ptr<Quest> const &getCurrentQuest();
	void setCurrentQuest(std::shared_ptr<Quest> quest);
	void travelToVillage();

	QuestHandler(){};
};

