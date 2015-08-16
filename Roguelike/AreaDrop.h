#pragma once
#include "Area.h"
#include "Creature.h"
#include <vector>

class AreaDrop
{
private:
	std::vector<std::pair<std::string, std::pair<std::string, double>>> creaturesRarityChance;

public:

	void drop(Point2D &location, int dropAreaSize, Area &area);

	AreaDrop(std::vector<std::pair<std::string, std::pair<std::string, double>>> creaturesRarityChance) :
		creaturesRarityChance(creaturesRarityChance){};
};

