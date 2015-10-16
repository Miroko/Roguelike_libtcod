#include "Pathfinder.h"
#include "Direction.h"

int Pathfinder::getMovementCost(PathLocation &from, const Point2D &direction, Point2D &to, std::function<int(Point2D &toLocation)>& getMovementCostCallback){
	int movementCost = getMovementCostCallback(to);
	if (movementCost == INT_MAX) return movementCost;
	else return from.movementCostSoFar + movementCost;
}

int Pathfinder::getHeuristicValue(PathLocation& fromLocation, Point2D& fromCoordinates, Point2D& toCoordinates){
	return fromLocation.movementCostSoFar + fromCoordinates.distanceChebyshev(toCoordinates);
}

Pathfinder::Path Pathfinder::computePath(Point2D &start, Point2D &goal, std::function<int(Point2D &toLocation)> getMovementCostCallback){
	locationsWithHeuristic.push_front(PathLocationHeuristic(start, 0));
	locations[start.x][start.y].movementCostSoFar = 0;
	while (!locationsWithHeuristic.empty()){
		PathLocationHeuristic currentLocationWithHeuristic = locationsWithHeuristic.front();
		if (currentLocationWithHeuristic.location == goal) break;
		else locationsWithHeuristic.pop_front();

		PathLocation currentLocation = locations[currentLocationWithHeuristic.location.x][currentLocationWithHeuristic.location.y];
		for (auto& direction : DIRECTIONS){
			Point2D nextCoordinates = currentLocationWithHeuristic.location + direction;
			if (!bounds.inside(nextCoordinates)) continue;

			//cost to move to this location from start
			int movementCost = getMovementCost(currentLocation, direction, nextCoordinates, getMovementCostCallback);
			if (movementCost == INT_MAX) continue; //unpassable

			PathLocation& nextLocation = locations[nextCoordinates.x][nextCoordinates.y];
			if (movementCost >= nextLocation.movementCostSoFar) continue;		
			nextLocation.cameFrom = currentLocationWithHeuristic.location;
			nextLocation.movementCostSoFar = movementCost;
			coordinatesNeedingReset.push_back(nextCoordinates);

			int heuristicValue = getHeuristicValue(nextLocation, nextCoordinates, goal);
			auto& locationIterator = locationsWithHeuristic.begin();
			while (true){
				if (locationIterator == locationsWithHeuristic.end()){
					locationsWithHeuristic.emplace_back(nextCoordinates, heuristicValue);
					break;
				}
				else if (locationIterator->heuristicValue >= heuristicValue){
					locationsWithHeuristic.emplace(locationIterator, nextCoordinates, heuristicValue);
					break;
				}
				else locationIterator++;
			}
		}
	}
	//build path and reset data
	locationsWithHeuristic.clear();
	locations[start.x][start.y].reset();
	std::deque<Point2D> pathLocations;
	PathLocation &location = locations[goal.x][goal.y];
	if (location.isAssigned()){
		//path found
		//build reversed from destination
		while (location.isAssigned()){
			pathLocations.push_front(location.cameFrom);
			if (location.cameFrom == start) break;
			location = locations[location.cameFrom.x][location.cameFrom.y];
		}
		pathLocations.push_back(goal); //add goal to path
	}
	//reset
	for (auto &location : coordinatesNeedingReset){
		locations[location.x][location.y].reset();
	}
	coordinatesNeedingReset.clear();
		
	return Path(pathLocations);
}

Pathfinder::Pathfinder(int xMax, int yMax) :
	bounds(Rectangle(xMax, yMax)){
	locations.resize(bounds.getWidth());
	for (int x = bounds.start.x; x < bounds.end.x; ++x){
		locations[x].resize(bounds.getHeight());
	}
	coordinatesNeedingReset.reserve(bounds.getSize() / 3);
}

//Path class

Point2D& Pathfinder::Path::getCurrentLocation(){
	return locations.at(currentLocationIndex);
}

Point2D& Pathfinder::Path::getDestination(){
	return locations.at(locations.size() - 1);
}

Point2D& Pathfinder::Path::getAt(int index){
	return locations.at(index);
}

Point2D& Pathfinder::Path::getNextLocation(){
	return
		currentLocationIndex < (int)(locations.size() - 1) ?
		locations.at(currentLocationIndex + 1) :
		locations.at(currentLocationIndex);
}

Point2D& Pathfinder::Path::getPreviousLocation(){
	return 
		currentLocationIndex > 0 ?
		locations.at(currentLocationIndex - 1) :
		locations.at(currentLocationIndex);
}

void Pathfinder::Path::next(){
	if (currentLocationIndex < (int)(locations.size() - 1)) currentLocationIndex++;
}

void Pathfinder::Path::previous(){
	if (currentLocationIndex > 0) currentLocationIndex--;
}

int Pathfinder::Path::getCurrentIndex(){
	return currentLocationIndex;
}

int Pathfinder::Path::remainingDistance(){
	if (locations.empty()) return 0;
	return (locations.size() - 1) - currentLocationIndex;
}

int Pathfinder::Path::size(){
	return locations.size();
}