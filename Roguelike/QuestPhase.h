#pragma once
#include "Area.h"
#include <string>
class QuestPhase
{
public:
	std::string name;

	virtual void generateArea(Area &area) = 0;

	QuestPhase(){};
};