#pragma once
#include "Area.h"

class QuestPhase;
class AreaHandler
{
public:
	std::shared_ptr<Area> currentArea = nullptr;
	std::vector<std::pair<std::shared_ptr<QuestPhase>, std::shared_ptr<Area>>> savedPhaseAreas;

	void setCurrentArea(std::shared_ptr<Area> area);
	std::shared_ptr<Area> &getCurrentArea();
	void saveCurrentArea();
	bool loadSavedArea(std::shared_ptr<QuestPhase> persistentPhase);

	void updateArea();
	void cleanDeadObjects();
	void renderArea();

	AreaHandler(){};
};

