#pragma once
#include "Rectangle.h"
#include <string>

class AreaDrop;
class Door;
class Tile;
class Area;
class AreaHouse
{
public:
	Point2D doorLocation;
	Rectangle bounds;
	Tile &wall;
	Tile &floor;
	std::string doorId;
	AreaDrop &residentDrop;
	std::vector<std::pair<std::string, double>> furnitureChances;

	void build(Rectangle &bounds, Area &area);

	AreaHouse(
		std::string wallId,
		std::string floorId,
		std::string doorId,
		AreaDrop &residentDrop,
		std::vector<std::pair<std::string, double>> furnitureChances);
};

