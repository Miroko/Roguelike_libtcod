#pragma once
#include "Area.h"

class AreaPath
{
public:
	Tile &pathTile;
	Area &area;
	std::vector<Tile*> blockingTiles;
	std::vector<Tile*> overlayTiles;
	Point2D destination;
	double weightToUseExistingPath;
	int width;
	double diagonalCost;

	std::shared_ptr<TCODPath> pathMap;
	class PathCostCallback : public ITCODPathCallback{ public: float getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const; };
	void createPathMap(Area &area);

	void build(Point2D &from, Point2D &to);

	AreaPath(Tile &pathTile, Area &area, std::vector<Tile*> blockingTiles, std::vector<Tile*> overlayTiles, double weightToUseExistingPath, int width = 1, double diagonalCost = 1.41f) :
		pathTile(pathTile), area(area), blockingTiles(blockingTiles), overlayTiles(overlayTiles), weightToUseExistingPath(weightToUseExistingPath), width(width), diagonalCost(diagonalCost){};
};
