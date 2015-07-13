#include "Cave.h"
#include "Direction.h"
#include "AreaPath.h"
#include "Engine.h"

Cave::Cave(std::string wall1Id, std::string wall2Id, std::string floor1Id, std::string floor2Id, std::string waterId, std::string portalId, std::string roomWallId, AreaDrop &roomDrop,
	int size, float corridorsPerTile, int corridorSize, float roomChance, float roomDropChance, int roomSize, float riverPercentage, int portals) :
	wall1(*engine::objectLibrary.getTile(wall1Id)),
	wall2(*engine::objectLibrary.getTile(wall2Id)),
	floor1(*engine::objectLibrary.getTile(floor1Id)),
	floor2(*engine::objectLibrary.getTile(floor2Id)),
	roomWall(*engine::objectLibrary.getTile(roomWallId)),
	water(*engine::objectLibrary.getTile(waterId)),
	portal(*engine::objectLibrary.getTile(portalId)),
	size(size),
	corridorsPerTile(corridorsPerTile),
	corridorSize(corridorSize),
	roomChance(roomChance),
	roomSize(roomSize),
	riverPercentage(riverPercentage),
	portals(portals),
	roomDrop(roomDrop),
	roomDropChance(roomDropChance){
}
void Cave::generate(){
	generateBase(Rectangle(size,size), wall1);

	//common
	Rectangle innerBounds = Rectangle(getBounds());
	innerBounds.shrink(1);
	Point2D nextLocation;
	Point2D randomDirection;
	Point2D newLocation;

	//generate cave
	nextLocation = innerBounds.getCenterPoint();
	int corridors = (int)(innerBounds.getSize() * corridorsPerTile);
	int floorTiles = 0;
	while (corridors > 0){
		//Next direction
		int currentCorridorSize = corridorSize;
		while (currentCorridorSize > 0){
			//Place corridor
			placeTile(floor1, nextLocation);
			++floorTiles;
			//Place room
			if (engine::random.generator->getFloat(0.0, 1.0) <= roomChance){
				Rectangle roomBounds = Rectangle(nextLocation, nextLocation);
				roomBounds.expand(roomSize);
				for (Point2D &edgeLocation : roomBounds.getEdgePoints()){
					if (getTile(edgeLocation) == &wall1){
						placeTile(roomWall, edgeLocation);
					}
				}
				roomBounds.shrink(1);
				Point2D locationInRoom;
				for (int x = roomBounds.start.x; x <= roomBounds.end.x; x++){
					for (int y = roomBounds.start.y; y <= roomBounds.end.y; y++){
						locationInRoom.x = x;
						locationInRoom.y = y;
						if (innerBounds.contains(locationInRoom)){
							placeTile(floor2, locationInRoom);
							++floorTiles;
						}
					}
				}
				if (engine::random.chance(roomDropChance)){
					roomDrop.drop(roomBounds.getCenterPoint(), 3, *this);
				}
			}
			//Next location
			randomDirection = engine::random.direction();
			newLocation = nextLocation + randomDirection;
			if (!innerBounds.contains(newLocation)){
				newLocation = nextLocation - randomDirection;
			}
			nextLocation = newLocation;

			--currentCorridorSize;
		}
		--corridors;
	}
	generateEdge(wall1, 0, 0);

	//rivers
	std::vector<Tile*> blockingTiles;
	blockingTiles.push_back(&wall1);
	AreaPath riverPather = AreaPath(water, *this, blockingTiles, {}, 0.3f, 2);
	int rivers = (int)((floorTiles / (50 * 50)) * riverPercentage);
	for (int river = rivers; river > 0; --river){
		Point2D start = getNearestTile(engine::random.point(innerBounds), floor2);
		Tile* atpos = getTile(start);
		Point2D end = getNearestTile(engine::random.point(innerBounds), floor2);
		atpos = getTile(end);
		riverPather.build(start, end);
	}

	//portals
	for (int portalNumber = portals; portalNumber > 0; --portalNumber){
		placeTile(portal, engine::random.point(innerBounds), floor2);
	}
}
