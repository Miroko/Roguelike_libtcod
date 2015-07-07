#include "Forest.h"
#include "Engine.h"

Forest::Forest(std::string landId, std::string treeId, std::string stoneHighId, std::string stoneLowId, std::string portalId,
	int size, float treePercentage, float stonePercentage, int portals, float treeDistribution, int treeThickness) :
	land(*engine::objectLibrary.getTile(landId)),
	tree(*engine::objectLibrary.getTile(treeId)),
	stoneLow(*engine::objectLibrary.getTile(stoneLowId)),
	stoneHigh(*engine::objectLibrary.getTile(stoneHighId)),
	portal(*engine::objectLibrary.getTile(portalId)),
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
					if (getTile(locationA)->type == GameObject::WALL ||
						getTile(locationB)->type == GameObject::WALL){
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

	generateEdge(tree, 1, 4);

	for (int portalNumber = portals; portalNumber > 0; --portalNumber){
		Point2D location = engine::random.point(getBounds());
		placeTile(portal, location, land);
	}
}

void Forest::onGatePlace(Point2D &location){

}

void Forest::onStonePlaced(Point2D &location){

}