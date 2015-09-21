#include "ParticleSplash.h"
#include "Engine.h"

void ParticleSplash::onTick(){
	location += engine::random.direction();
}

std::shared_ptr<Particle> ParticleSplash::clone(){
	return std::shared_ptr<Particle>(new ParticleSplash(*this));
}