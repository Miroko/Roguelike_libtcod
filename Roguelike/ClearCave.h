#pragma once
#include "Quest.h"

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
	std::shared_ptr<QuestPhase> Quest::getNextPhase();
};