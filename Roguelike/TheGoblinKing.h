#pragma once
#include "Quest.h"

class TheGoblinKing : public Quest{
	class WayToCave : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		bool QuestPhase::winCondition();
		WayToCave() : QuestPhase("-Find a way to the cave."){};
	};
	class CaveEntrance : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		bool QuestPhase::winCondition();
		CaveEntrance() : QuestPhase("-Find a way to the cave."){};
	};
	class InTheCave : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		bool QuestPhase::winCondition();
		InTheCave() : QuestPhase("-Kill the goblin king."){};
	};
	class InVillage : public QuestPhase{
	public:
		void QuestPhase::generateArea(Area &area);
		bool QuestPhase::winCondition();
		InVillage() : QuestPhase("-Find a way to the cave."){};
	};
public:
	std::shared_ptr<QuestPhase> Quest::getNextPhase();
	std::shared_ptr<QuestPhase> Quest::getVillage();

	TheGoblinKing() : Quest("The Goblin King"){}
};