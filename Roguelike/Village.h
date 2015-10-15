#pragma once
#include "Area.h"
#include "AreaDen.h"
#include "AreaDrop.h"

class Village : public Area
{
public:
	std::vector<AreaDen> houses;
	Rectangle villageBounds;

	int size;
	Tile &land;
	Tile &tree;
	Tile &stoneHigh;
	Tile &stoneLow;
	Tile &path;
	std::vector<std::pair<AreaDen*, double>> houseChances;

	void Area::generate();

	Village(
		std::string landId,
		std::string treeId,
		std::string stoneHighId,
		std::string stoneLowId,
		std::string pathId,
		int size,
		std::vector<std::pair<AreaDen*, double>> houseChances);
};
