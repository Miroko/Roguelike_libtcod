#pragma once
#include "Area.h"

class Forest : public Area
{
private:
	int size;
	float treePercentage;
	float stonePercentage;
	float treeDistribution;
	int treeThickness;
	int portals;
	Tile &land;
	Tile &tree;
	Tile &stoneHigh;
	Tile &stoneLow;
	Tile &portal;

public:	
	void Area::generate();

	virtual void onGatePlace(Point2D &location);
	virtual void onStonePlaced(Point2D &location);

	Forest(std::string landId, std::string treeId, std::string stoneHighId, std::string stoneLowId, std::string portalId,
		int size, float treePercentage, float stonePercentage, int portals = -1, float treeDistribution = 0.07f, int treeThickness = 2);
};

