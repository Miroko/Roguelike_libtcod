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

class ClearCave : public Quest{
	class WayToCave : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		WayToCave() : QuestPhase(){};
	};
	class CaveEntrance : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		CaveEntrance() : QuestPhase(){};
	};
	class InTheCave : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		InTheCave() : QuestPhase(){};
	};
public:
	std::shared_ptr<QuestPhase> getNextPhase();
};