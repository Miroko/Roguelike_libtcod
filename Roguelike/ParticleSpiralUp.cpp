#include "ParticleSpiralUp.h"
#include "Engine.h"
#include "Direction.h"

void ParticleSpiralUp::onTick(){
	double directionRoll = engine::random.generator->getDouble(0.0, 1.0);
	if (directionRoll < 0.20) location += LEFT;
	else if (directionRoll < 0.40) location += RIGHT;
	else location += UP;
}

std::shared_ptr<Particle> ParticleSpiralUp::clone(){
	return std::shared_ptr<Particle>(new ParticleSpiralUp(*this));
}