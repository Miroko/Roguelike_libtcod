#pragma once
#include "Area.h"

class AreaHandler
{
private:
	std::shared_ptr<Area> currentArea;

public:
	void setCurrentArea(std::shared_ptr<Area> area);
	std::shared_ptr<Area> &getCurrentArea();

	void updateArea();
	void renderArea();

	AreaHandler(){};
};

