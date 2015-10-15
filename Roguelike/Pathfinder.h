#pragma once
#include "Point2D.h"
#include "Rectangle.h"
#include <deque>
#include <functional>
#include <list>

//http://theory.stanford.edu/~amitp/GameProgramming/#pathfinding

//Custom implementation of A* algorithm
class Pathfinder
{
private:
	struct PathLocation{
		Point2D cameFrom;
		int movementCostSoFar;

		void reset(){ movementCostSoFar = INT_MAX; }
		bool isAssigned(){ return movementCostSoFar != INT_MAX; }

		PathLocation(){ reset(); }
	};
	struct PathLocationHeuristic{
		Point2D location;
		int heuristicValue;

		PathLocationHeuristic(Point2D &location, int heuristicValue) :
			location(location),
			heuristicValue(heuristicValue){}
	};

	Rectangle bounds;
	std::vector<std::vector<PathLocation>> locations;
	std::list<PathLocationHeuristic> locationsWithHeuristic;
	std::vector<Point2D> coordinatesNeedingReset;

	int getMovementCost(PathLocation& from, Point2D& direction, Point2D& to, std::function<int(Point2D &toLocation)>& getMovementCostCallback);
	int getHeuristicValue(PathLocation& fromLocation, Point2D& fromCoordinates, Point2D& toCoordinates);

public:
	class Path{
	private:
		int currentLocationIndex;
		std::deque<Point2D> locations;

	public:
		Point2D& getCurrentLocation();
		Point2D& getDestination();
		Point2D& getAt(int index);
		Point2D& getNextLocation();
		Point2D& getPreviousLocation();
		void next();
		void previous();
		int getCurrentIndex();
		int remainingDistance();
		int size();

		Path(std::deque<Point2D> locations) :
			locations(locations),
			currentLocationIndex(0){}
		Path(){}
	};

	//Best-First-Search when movement cost == 0
	//Shortest path when movement cost == 1
	//Movement cost > 1 obstacle to avoid
	//Movement cost == INT_MAX unpassable obstacle
	//For optimal performance use movement cost near 0 and INT_MAX for unpassable
	Path computePath(Point2D &start, Point2D &goal, std::function<int(Point2D &toLocation)> getMovementCostCallback);

	Pathfinder(int xMax, int yMax);
};

