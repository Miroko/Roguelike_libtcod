#pragma once
#include "Area.h"

class AreaHandler
{
public:
	std::shared_ptr<Area> currentArea = nullptr;
	std::shared_ptr<Area> savedArea = nullptr;

	void setCurrentArea(std::shared_ptr<Area> area);
	std::shared_ptr<Area> &getCurrentArea();
	void saveCurrentArea();
	void loadSavedArea();

	void updateArea();
	void renderArea();

	AreaHandler(){};
};

