#include "AiFov.h"
#include "libtcod.hpp"
#include "Engine.h"

double AiFov::getLuminosity(Point2D &fromLocation, Point2D &toLocation){
	int x = centerLocation.x - (fromLocation.x - toLocation.x);
	int y = centerLocation.y - (fromLocation.y - toLocation.y);
	if (x >= size || y >= size || x < 0 || y < 0) return 0.0;
	return luminosities[x][y];
}

void AiFov::castRay(Point2D &fromAreaLocation, Point2D &toLuminositiesArrayLocation){
	Point2D rayLocation;
	Point2D rayLocationInArea;
	double rayLuminosity = 1.0;
	int distance = 0;
	TCODLine::init(
		centerLocation.x,
		centerLocation.y,
		toLuminositiesArrayLocation.x,
		toLuminositiesArrayLocation.y);
	while (!TCODLine::step(&rayLocation.x, &rayLocation.y)){
		luminosities[rayLocation.x][rayLocation.y] = rayLuminosity;
		rayLocationInArea.x = fromAreaLocation.x + (rayLocation.x - centerLocation.x);
		rayLocationInArea.y = fromAreaLocation.y + (rayLocation.y - centerLocation.y);
		if (!engine::areaHandler.getCurrentArea()->isTransparent(rayLocationInArea)) break;
		if (distance >= luminosityDropDistance) rayLuminosity += luminosityDropPerDistance;
		++distance;
	}
}

void AiFov::compute(Point2D &fromLocation){
	//reset
	for (int x = 0; x < size; ++x){
		for (int y = 0; y < size; ++y){
			luminosities[x][y] = 0.0;
		}
	}
	//center
	luminosities[centerLocation.x][centerLocation.y] = 1.0;
	//rays
	Point2D castRayLocationA = Point2D(0, 0);
	Point2D castRayLocationB = Point2D(0, size - 1);
	for (int x = 0; x < size; ++x){
		castRayLocationA.x = x;
		castRayLocationB.x = x;
		castRay(fromLocation, castRayLocationA);
		castRay(fromLocation, castRayLocationB);
	}
	castRayLocationA.x = 0;
	castRayLocationB.x = size - 1;
	castRayLocationB.y = 0;
	for (int y = 0; y < size; ++y){
		castRayLocationA.y = y;
		castRayLocationB.y = y;
		castRay(fromLocation, castRayLocationA);
		castRay(fromLocation, castRayLocationB);
	}
}