#pragma once
#include "Area.h"

class AreaTreeSpot
{
public:
	Tile &tree;
	int trees;
	int branches;
	Point2D &location;
	std::vector<Tile*> blockTiles;

	void grow(Area &area);
	virtual void onGatePlaced(Point2D &location);

	AreaTreeSpot(Tile &tree, int trees, int branches, Point2D &location, std::vector<Tile*> blockTiles) :
		tree(tree), trees(trees), branches(branches), location(location), blockTiles(blockTiles){};
};

