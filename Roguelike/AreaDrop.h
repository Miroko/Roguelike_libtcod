#pragma once
#include "Area.h"
#include "Creature.h"
#include <vector>

class AreaDen;
class AreaDrop
{
public:
	std::vector<std::pair<std::string, std::pair<std::string, double>>> creaturesRarityChance;
	std::vector<std::pair<std::string, std::pair<std::string, double>>> operatablesRarityChance;

	void drop(Rectangle &dropBounds, Area &area);
	void drop(AreaDen &toDen, Area &area);

	AreaDrop(
		std::vector<std::pair<std::string, std::pair<std::string, double>>> creaturesRarityChance,
		std::vector<std::pair<std::string, std::pair<std::string, double>>> operatablesRarityChance = {})
		:
		creaturesRarityChance(creaturesRarityChance),
		operatablesRarityChance(operatablesRarityChance){};
};

