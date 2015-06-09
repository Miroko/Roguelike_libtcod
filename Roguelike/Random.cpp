#include "Random.h"

TCODRandom Random::generator = TCODRandom(123456789, TCOD_RNG_CMWC);

Point2D Random::point(Rectangle &inBounds){
	return Point2D(generator.getInt(inBounds.start.x, inBounds.end.x - 1),
		           generator.getInt(inBounds.start.y, inBounds.end.y - 1));
}

Point2D Random::direction(){
	int r = generator.getInt(0, 7);
	return DIRECTIONS[r];
}