#pragma once
#include "Area.h"

class AreaPath
{
public:
	Tile &pathTile;
	Area &area;
	std::vector<Tile*> blockingTiles;
	Tile &overlay;
	Point2D destination;

	std::shared_ptr<TCODPath> pathMap;
	class PathCostCallback : public ITCODPathCallback{ public: float getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const; };
	void createPathMap(Area &area);

	void build(Point2D &from, Point2D &to);

	AreaPath(Tile &pathTile, Area &area, std::vector<Tile*> blockingTiles, Tile &overlay) :
		pathTile(pathTile), area(area), blockingTiles(blockingTiles), overlay(overlay){};
};
