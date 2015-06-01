#pragma once
#include "Area.h"
class QuestPhase
{
public:
	virtual void generateArea(Area &area) = 0;

	QuestPhase(){};
};