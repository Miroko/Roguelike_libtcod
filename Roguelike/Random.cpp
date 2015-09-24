#include "Random.h"
#include "Direction.h"
#include <math.h>

Point2D Random::point(Rectangle &inBounds){
	return Point2D(generator->getInt(inBounds.start.x, inBounds.end.x),
		           generator->getInt(inBounds.start.y, inBounds.end.y));
}

Point2D Random::direction(){
	int index = generator->getInt(0, 7);
	return DIRECTIONS[index];
}

void Random::useRandom(){
	//Restore saved state
	generator->restore(randomState.get());
}

bool Random::chance(double min){
	if (min <= 0.0) return false;
	else if (min >= 1.0) return true;
	else return generator->getDouble(0.0, 1.0) < min;
}

bool Random::chancePercentage(double percentage){
	return generator->getInt(0, percentage * 100) != 0;
}

double Random::variationMultiplier(double variation){
	return generator->getDouble(1.0 - variation, 1.0);
}

void Random::useStatic(){
	//Save random state
	randomState.reset(generator->save());
	//Set generator to use static state
	generator->restore(staticState.get());
}

void Random::init(){
	generator = std::shared_ptr<TCODRandom>(new TCODRandom(TCOD_RNG_CMWC));
	randomState.reset(generator->save());
	staticState.reset(generator->save());
}