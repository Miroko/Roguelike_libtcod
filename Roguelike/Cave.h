#pragma once
#include "Area.h"
#include "AreaDrop.h"

class Cave : public Area
{
private:
	int size;
	double corridorsPerTile;
	int corridorSize;
	double roomChance; 
	double roomDropChance;
	int roomSize;
	double riverPercentage;
	int portals;
	AreaDrop &roomDrop;
	Tile &wall1;
	Tile &wall2;
	Tile &floor1;
	Tile &floor2;
	Tile &roomWall;
	Tile &water;
	Tile &portal;

public:
	void Area::generate();

	Cave(std::string wall1Id, std::string wall2Id, std::string floor1Id, std::string floor2Id, std::string waterId, std::string portalId, std::string roomWallId, AreaDrop &roomDrop,
		int size, double corridorsPerTile, int corridorLength, double roomChance, double roomRropChance, int roomSize, double riverPercentage, int portals);
};
