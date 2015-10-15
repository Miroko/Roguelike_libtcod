#pragma once
#include "Rectangle.h"
#include <string>

class AreaDrop;
class Door;
class Tile;
class Area;
class AreaDen
{
public:
	Point2D doorLocation;
	Rectangle bounds;
	Tile &wall;
	Tile &floor;
	std::string doorId;
	AreaDrop &areaDrop;

	void build(Rectangle &bounds, Area &area);

	AreaDen(
		std::string wallId,
		std::string floorId,
		std::string doorId,
		AreaDrop &areaDrop);
};

