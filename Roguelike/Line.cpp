#include "Line.h"
#include "libtcod.hpp"

Line::Line(Point2D &start, Point2D &end){
	TCODLine::init(start.x, start.y, end.x, end.y);
	
	int x = start.x;
	int y = start.y;
	do{
		points.push_back(std::shared_ptr<Point2D>(new Point2D(x, y)));
	} while (TCODLine::step(&x, &y) == false);
}