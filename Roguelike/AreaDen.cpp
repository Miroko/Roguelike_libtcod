#include "AreaDen.h"
#include "Area.h"
#include "Engine.h"
#include "Direction.h"
#include "AreaDrop.h"

AreaDen::AreaDen(
	std::string wallId,
	std::string floorId,
	std::string doorId,
	AreaDrop &areaDrop) :
	wall(*engine::objectLibrary.tiles[wallId]),
	floor(*engine::objectLibrary.tiles[floorId]),
	doorId(doorId),
	areaDrop(areaDrop){
}

void AreaDen::build(Rectangle &bounds, Area &area){
	this->bounds = bounds;

	std::vector<Point2D> wallPoints = bounds.getEdgePoints();
	//Wall
	for (Point2D p : wallPoints){
		area.placeTile(wall, p);
	}
	//Floor
	for (int x = bounds.start.x + 1; x < bounds.end.x; ++x){
		for (int y = bounds.start.y + 1; y < bounds.end.y; ++y){
			area.placeTile(floor, Point2D(x, y));
		}
	}
	//place door, corner locations invalid
	bool placed = false;
	while (!placed){
		bool adjacentHorizontal = false;
		bool adjacentVertical = false;
		int adjacentWalls = 0;
		Point2D doorPoint = wallPoints.at(engine::random.generator->getInt(0, wallPoints.size() - 1));
		for (Point2D &point : wallPoints){
			if (doorPoint + LEFT == point && !adjacentVertical){
				adjacentHorizontal = true;
				adjacentWalls++;
			}
			if (doorPoint + RIGHT == point && !adjacentVertical){
				adjacentHorizontal = true;
				adjacentWalls++;
			}
			if (doorPoint + UP == point && !adjacentHorizontal){
				adjacentVertical = true;
				adjacentWalls++;
			}
			if (doorPoint + DOWN == point && !adjacentHorizontal){
				adjacentVertical = true;
				adjacentWalls++;
			}
			if (adjacentWalls == 2){
				area.placeTile(floor, doorPoint);
				area.placeOperatable(engine::objectFactory.createOperatable(doorId), doorPoint);
				doorLocation = doorPoint;
				placed = true;
				break;
			}
		}
	}
	areaDrop.drop(*this, area);
}