#include "AreaPath.h"

void AreaPath::build(Point2D &from, Point2D &to){
	Pathfinder::Path path = area.pathFinder.computePath(from, to, [&](Point2D& toLocation){
		auto &areaContainer = area.areaContainers[toLocation.x][toLocation.y];
		if (areaContainer.tile == &pathTile) return movementCostOnExisting;
		for (Tile* blockingTile : blockingTiles){
			if (areaContainer.tile == blockingTile) return INT_MAX;
		}
		return movementCost;
	});

	while (path.remainingDistance() > 0){
		Point2D currentLocation = path.getCurrentLocation();
		bool placeTile = true;
		for (auto &tile : overlayTiles){
			if (area.getTile(currentLocation) == tile) placeTile = false;
		}
		if (placeTile){
			Rectangle placeArea = Rectangle(currentLocation, width / 2);
			Point2D innerLocation;
			for (innerLocation.x = placeArea.start.x; innerLocation.x <= placeArea.end.x; ++innerLocation.x){
				for (innerLocation.y = placeArea.start.y; innerLocation.y <= placeArea.end.y; ++innerLocation.y){
					for (Tile *blockingTile : blockingTiles){
						if (area.areaContainers[innerLocation.x][innerLocation.y].tile == blockingTile) placeTile = false;
					}
					if (placeTile){
						area.placeTile(pathTile, innerLocation);
					}
				}
			}
		}
		path.next();
	}
}