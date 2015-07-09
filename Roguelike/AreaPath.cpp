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
				area.placeTile(pathTile, pathLocation);
			}
		}
	}
}

float AreaPath::PathCostCallback::getWalkCost(int xFrom, int yFrom, int xTo, int yTo, void *userData) const{
	AreaPath *thisObject = static_cast<AreaPath*>(userData);
	for (Tile *blockingTile : thisObject->blockingTiles){
		if (thisObject->area.tiles[xTo][yTo] == blockingTile) return 0;
	}
	if (thisObject->area.tiles[xTo][yTo] == &thisObject->pathTile) return 0.1f; //prefer to use existing paths
	return 1;
}
void AreaPath::createPathMap(Area &area){
	pathMap = std::shared_ptr<TCODPath>(new TCODPath(
		area.getBounds().getWidth(),
		area.getBounds().getHeight(),
		new PathCostCallback(),
		this,
		0));
}