#include "WorldArea.h"


WorldArea::WorldArea(int size){
	this->bounds = Rectangle(Point2D(0, 0), Point2D(size, size));


	staticObjects.resize(bounds.getWidth());
	for (int x = 0; x < bounds.getWidth(); x++){
		staticObjects[x].resize(bounds.getHeight(), LAND);
	}

	staticObjects[23][23] = WALL;
}