#pragma once
#include "Area.h"
#include <string>
#include <vector>
#include <memory>

class QuestPhase
{
public:
	std::string description;

	virtual void generateArea(Area &area) = 0;
	virtual bool nextPhaseCondition() = 0; 
	virtual void placePlayer();

	QuestPhase(std::string description) :
		description(description){};
};