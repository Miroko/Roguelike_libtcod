#pragma once
#include "Area.h"

class AreaPath
{
public:
	Tile &pathTile;
	Area &area;
	std::vector<Tile*> blockingTiles;
	std::vector<Tile*> overlayTiles;
	int movementCost;
	int movementCostOnExisting;
	int width;

	void build(Point2D &from, Point2D &to);

	AreaPath(Tile &pathTile, Area &area, std::vector<Tile*> blockingTiles, std::vector<Tile*> overlayTiles, int movementCost, int movementCostOnExisting, int width = 1) :
		pathTile(pathTile), 
		area(area), 
		blockingTiles(blockingTiles), 
		overlayTiles(overlayTiles), 
		movementCost(movementCost),
		movementCostOnExisting(movementCostOnExisting),
		width(width){};
};
