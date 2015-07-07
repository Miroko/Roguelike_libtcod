#include "AreaHouse.h"
#include "Area.h"
#include "Engine.h"
#include "Direction.h"

void AreaHouse::build(std::shared_ptr<Door> door, AreaDrop &residents, Area &area){
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
	//Door, corners invalid
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
				area.placeOperatable(door, doorPoint);
				placed = true;
				break;
			}
		}
	}

	residents.drop(bounds.getCenterPoint(), 0, area);
}