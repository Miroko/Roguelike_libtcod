#include "ParticleSpark.h"
#include "Engine.h"

void ParticleSpark::onTick(){
	location += engine::random.direction();
}

std::shared_ptr<Particle> ParticleSpark::clone(){
	return std::shared_ptr<Particle>(new ParticleSpark(*this));
}