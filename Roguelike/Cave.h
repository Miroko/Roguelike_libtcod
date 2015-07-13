#pragma once
#include "Area.h"
#include "AreaDrop.h"

class Cave : public Area
{
private:
	int size;
	float corridorsPerTile;
	int corridorSize;
	float roomChance; 
	float roomDropChance;
	int roomSize;
	float riverPercentage;
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
		int size, float corridorsPerTile, int corridorLength, float roomChance, float roomRropChance, int roomSize, float riverPercentage, int portals);
};
