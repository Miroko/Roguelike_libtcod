#pragma once
#include "Area.h"

class AreaDrop;
class Forest : public Area
{
private:
	int size;
	double treePercentage;
	double stonePercentage;
	double treeDistribution;
	int treeThickness;
	int portals;
	Tile &land;
	Tile &tree;
	Tile &stoneHigh;
	Tile &stoneLow;
	Tile &portal;
	AreaDrop &areaDrop;

public:	
	void Area::generate();

	virtual void onGatePlace(Point2D &location);
	virtual void onStonePlaced(Point2D &location);

	Forest(std::string landId, std::string treeId, std::string stoneHighId, std::string stoneLowId, std::string portalId, AreaDrop &areaDrop,
		int size, double treePercentage, double stonePercentage, int portals, double treeDistribution = 0.07f, int treeThickness = 2);
};

