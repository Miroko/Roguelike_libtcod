#include "Random.h"

TCODRandom Random::generator = TCODRandom(TCOD_RNG_CMWC);
std::shared_ptr<TCODRandom> Random::randomState = std::shared_ptr<TCODRandom>(Random::generator.save());
std::shared_ptr<TCODRandom> Random::staticState = std::shared_ptr<TCODRandom>(Random::generator.save());

Point2D Random::point(Rectangle &inBounds){
	return Point2D(generator.getInt(inBounds.start.x, inBounds.end.x - 1),
		           generator.getInt(inBounds.start.y, inBounds.end.y - 1));
}

Point2D Random::direction(){
	int r = generator.getInt(0, 7);
	return DIRECTIONS[r];
}

void Random::useRandom(){
	//Restore saved state
	generator.restore(randomState.get());
}

void Random::useStatic(){
	//Save state
	randomState.reset(generator.save());
	//Set to use static state
	generator.restore(staticState.get());
}

void Random::reset(){
	generator.getInt(0, 1);
	randomState = std::shared_ptr<TCODRandom>(Random::generator.save());
	staticState = std::shared_ptr<TCODRandom>(Random::generator.save());
}