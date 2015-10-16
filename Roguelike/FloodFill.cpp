#include "FloodFill.h"
#include "Direction.h"

void FloodFill::flood(
	Rectangle &bounds,
	double percentage,
	std::function<bool(Point2D &location)> isPassable,
	std::function<void(Point2D &location, int distance)> onLocationFill){
	locationStates.resize(bounds.getWidth() + 1);
	for (int x = 0; x < bounds.getWidth() + 1; ++x){
		locationStates[x].resize(bounds.getHeight() + 1, UNFILLED);
	}
	int locationsToFillTotal = bounds.getSize() * percentage;
	locations.push_back(bounds.getCenterPoint());
	for (int locationsLeft = locationsToFillTotal; locationsLeft > 0; --locationsLeft){
		if (locations.empty()) break;
		auto& location = locations.front();
		//fill location
		Point2D relativeLocation = location - bounds.start;
		locationStates[relativeLocation.x][relativeLocation.y] = FILLED;
		onLocationFill(location, locationsToFillTotal / locationsLeft);
		//get next locations
		for (auto& direction : DIRECTIONS){
			Point2D newLocation = location + direction;
			if (!bounds.contains(newLocation)) continue;
			Point2D newLocationRelative = newLocation - bounds.start;
			LocationState& locationState = locationStates[newLocationRelative.x][newLocationRelative.y];
			if (locationState == FILLED || locationState == FILL_NEXT) continue;
			if (!isPassable(newLocation)) continue;
			locationState = FILL_NEXT;
			locations.push_back(newLocation);
		}
		locations.pop_front();
	}
}