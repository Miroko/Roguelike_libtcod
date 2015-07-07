#pragma once
#include "Area.h"
#include "AreaHouse.h"
#include "AreaDrop.h"

class Village : public Area
{
public:
	std::vector<AreaHouse> houses;
	Rectangle villageBounds;
	AreaDrop &residents;
	int size;
	Tile &land;
	Tile &tree;
	Tile &houseWall;
	Tile &houseFloor;
	Tile &path;
	std::string doorId;

	void Area::generate();

	Village(
		std::string landId,
		std::string treeId,
		std::string houseWallId,
		std::string houseFloorId,
		std::string pathId,
		std::string doorId,
		int size,
		AreaDrop &residents);
};
