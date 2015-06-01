#include "PathFinder.h"

float Callback::getWalkCost(int fromX, int fromY, int toX, int toY, void *data) const{
	return 1;
}

PathFinder::PathFinder(Rectangle bounds){
	pathComputerAStar = &TCODPath(bounds.getWidth(), bounds.getHeight(), &Callback(), NULL);
}