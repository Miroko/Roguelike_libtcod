#include "TreeSpot.h"
#include "Engine.h"

void TreeSpot::grow(Area &area){
	int treesPerBranch = trees / branches;
	for (int branch = branches; branch > 0; --branch){
		int halfTreesPerBranch = treesPerBranch / 2;
		Point2D locationA = location;
		Point2D locationB = location;
		for (int twoBranchTrees = halfTreesPerBranch * 2; twoBranchTrees > 0; --twoBranchTrees){
			//scan two steps
			locationA += engine::random.direction();
			locationB = locationA + engine::random.direction();
			if (area.getBounds().contains(locationA) && area.getBounds().contains(locationB)){
				bool blocked = false;
				for (Tile *blockTile : blockTiles){
					if (area.getTile(locationA) == blockTile ||
						area.getTile(locationB) == blockTile){
						//wall touched, stop
						blocked = true;
						onGatePlaced(locationA);
						break;
					}
				}				
				if (!blocked){
					//grow
					area.placeTile(tree, locationA);
					area.placeTile(tree, locationB);
				}
			}
			else break;
		}
	}
}

void TreeSpot::onGatePlaced(Point2D &location){

}
