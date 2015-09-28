#include "AreaPath.h"

void AreaPath::build(Point2D &from, Point2D &to){
	destination = to;
	createPathMap(area);
	pathMap->compute(from.x, from.y, to.x, to.y);

	Point2D pathLocation;
	while (!pathMap->isEmpty()){
		if (pathMap->walk(&pathLocation.x, &pathLocation.y, false)){
			bool place = true;
			for (auto &tile : overlayTiles){
				if (area.getTile(pathLocation) == tile) place = false;
			}
			if (place){
				Rectangle placeArea = Rectangle(pathLocation, pathLocation);
				placeArea.expand(width / 2);
				Point2D innerLocation;
				for (innerLocation.x = placeArea.start.x; innerLocation.x <= placeArea.end.x; ++innerLocation.x){
					for (innerLocation.y = placeArea.start.y; innerLocation.y <= placeArea.end.y; ++innerLocation.y){
						bool place = true;
						for (Tile *blockingTile : blockingTiles){
							if (area.areaContainers[innerLocation.x][innerLocation.y].tile == blockingTile) place = false;
						}
						if (place){
							area.placeTile(pathTile, innerLocation);
						}
					}
				}				
			}
		}
	}
}

float AreaPath::PathCostCallback::getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const{
	AreaPath *thisObject = static_cast<AreaPath*>(userData);
	if (thisObject->area.areaContainers[xTo][yTo].tile == &thisObject->pathTile) return thisObject->weightToUseExistingPath; //prefer to use existing paths
	for (Tile *blockingTile : thisObject->blockingTiles){
		if (thisObject->area.areaContainers[xTo][yTo].tile == blockingTile) return 0;
	}
	return 1;
}
void AreaPath::createPathMap(Area &area){
	pathMap = std::shared_ptr<TCODPath>(new TCODPath(
		area.getBounds().getWidth(),
		area.getBounds().getHeight(),
		new PathCostCallback(),
		this,	
		diagonalCost));
}