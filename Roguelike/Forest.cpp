#include "Forest.h"
#include "AreaDrop.h"
#include "Engine.h"

Forest::Forest(std::string landId, std::string treeId, std::string stoneHighId, std::string stoneLowId, std::string portalId, AreaDrop &areaDrop,
	int size, double treePercentage, double stonePercentage, int portals, double treeDistribution, int treeThickness) :
	land(*engine::objectLibrary.tiles[landId]),
	tree(*engine::objectLibrary.tiles[treeId]),
	stoneLow(*engine::objectLibrary.tiles[stoneLowId]),
	stoneHigh(*engine::objectLibrary.tiles[stoneHighId]),
	portal(*engine::objectLibrary.tiles[portalId]),
	areaDrop(areaDrop),
	size(size),
	treePercentage(treePercentage),
	stonePercentage(stonePercentage),
	portals(portals),
	treeDistribution(treeDistribution),
	treeThickness(treeThickness){
	if (portals == -1){ portals = size / 25; }
}

void Forest::generate(){
	generateBase(Rectangle(size, size), land);

	//trees
	int trees = (int)(getBounds().getSize() * treePercentage);
	int treeAreas = (int)(getBounds().getSize() * treeDistribution);
	int branches = treeThickness;
	for (int treeArea = treeAreas; treeArea > 0; --treeArea){
		Point2D areaLocation = getNearestTile(engine::random.point(getBounds()), land);
		//location found
		int treesPerArea = trees / treeAreas;

		for (int branch = branches; branch > 0; --branch){
			int halfTreesPerBranch = treesPerArea / branches / 2;
			Point2D locationA = areaLocation;
			Point2D locationB = areaLocation;
			for (int twoBranchTrees = halfTreesPerBranch * 2; twoBranchTrees > 0; --twoBranchTrees){
				//scan two steps
				locationA += engine::random.direction();
				locationB = locationA + engine::random.direction();
				Rectangle b = getBounds();
				if (getBounds().contains(locationA) && getBounds().contains(locationB)){
					if (getTile(locationA)->isType(GameObject::WALL) ||
						getTile(locationB)->isType(GameObject::WALL)){
						//wall touched, stop
						onGatePlace(locationA);
						break;
					}
					else{
						//grow
						placeTile(tree, locationA);
						placeTile(tree, locationB);
					}
				}
				else break;
			}
		}			
	}

	//stones
	int stones = (int)(getBounds().getSize() * stonePercentage);
	for (int stoneNumber = stones; stoneNumber > 0; --stoneNumber){
		Point2D location = engine::random.point(getBounds());
		placeTile(stoneHigh, location, tree);
		onStonePlaced(location);

		Rectangle surrounding = Rectangle(location, location);
		surrounding.expand(2);
		for (int lowStone = engine::random.generator->getInt(1, 4); lowStone > 0; lowStone--){
			Point2D location = engine::random.point(surrounding);
			placeTile(stoneLow, location, land);
		}
	}

	//edge
	generateEdge(tree, 1, 4);

	//portals
	for (int portalNumber = portals; portalNumber > 0; --portalNumber){
		Point2D location = engine::random.point(getBounds());
		placeTile(portal, location, land);
	}

	//drops
	int drops = getBounds().getSize() / 500;
	for (int drop = drops; drop > 0; --drop){
		Point2D location = engine::random.point(getBounds());
		areaDrop.drop(location, 4, *this);
	}
}

void Forest::onGatePlace(Point2D &location){

}

void Forest::onStonePlaced(Point2D &location){

}