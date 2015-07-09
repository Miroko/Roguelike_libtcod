#pragma once
#include "Area.h"
#include "AreaHouse.h"
#include "AreaDrop.h"

class Village : public Area
{
public:
	std::vector<AreaHouse> houses;
	Rectangle villageBounds;

	int size;
	Tile &land;
	Tile &tree;
	Tile &stoneHigh;
	Tile &stoneLow;
	Tile &path;
	std::vector<std::pair<AreaHouse*, float>> houseChances;

	void Area::generate();

	Village(
		std::string landId,
		std::string treeId,
		std::string stoneHighId,
		std::string stoneLowId,
		std::string pathId,
		int size,
		std::vector<std::pair<AreaHouse* ,float>> houseChances);
};
