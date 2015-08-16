#include "AreaHouse.h"
#include "Area.h"
#include "Engine.h"
#include "Direction.h"
#include "AreaDrop.h"

AreaHouse::AreaHouse(
	std::string wallId,
	std::string floorId,
	std::string doorId,
	AreaDrop &residentDrop,
	std::vector<std::pair<std::string, double>> furnitureChances) :
	wall(*engine::objectLibrary.tiles[wallId]),
	floor(*engine::objectLibrary.tiles[floorId]),
	doorId(doorId),
	residentDrop(residentDrop),
	furnitureChances(furnitureChances){
}

void AreaHouse::build(Rectangle &bounds, Area &area){
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
	//furnitures
	Rectangle innerBounds = Rectangle(bounds);
	innerBounds.shrink(1);
	std::vector<Point2D> innerEdgePoints = innerBounds.getEdgePoints();
	std::list<Point2D> listOValidfInnerEdgePoints = std::list<Point2D>(innerEdgePoints.begin(), innerEdgePoints.end());
	//remove locations near door
	auto location = listOValidfInnerEdgePoints.begin();
	while (location != listOValidfInnerEdgePoints.end()){
		bool erase = false;
		for (Point2D const &direction : DIRECTIONS){
			if (*location + direction == doorLocation){
				erase = true;
			}
		}
		if (erase) location = listOValidfInnerEdgePoints.erase(location);
		else ++location;
	}
	//place furnitures randomly on valid locations
	for (auto &furnitureChance : furnitureChances){
		if (engine::random.generator->getFloat(0.0f, 1.0f) < furnitureChance.second){
			int randomIndex = engine::random.generator->getInt(0, listOValidfInnerEdgePoints.size() - 1);
			auto &location = listOValidfInnerEdgePoints.begin();
			std::advance(location, randomIndex);
			area.placeOperatable(engine::objectFactory.createOperatable(furnitureChance.first), *location);
			listOValidfInnerEdgePoints.remove(*location);
		}
	}

	//place residents
	residentDrop.drop(bounds.getCenterPoint(), 0, area);
}