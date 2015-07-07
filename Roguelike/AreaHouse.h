#pragma once
#include "Rectangle.h"
#include "AreaDrop.h"
#include "Door.h"
#include <string>

class Tile;
class Area;
class AreaHouse
{
public:
	Rectangle bounds;
	Tile &wall;
	Tile &floor;

	void build(std::shared_ptr<Door> door, AreaDrop &residents, Area &area);

	AreaHouse(Tile &wall, Tile &floor, Rectangle bounds) :
		wall(wall),
		floor(floor),
		bounds(bounds)
	{};
};

