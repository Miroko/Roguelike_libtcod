#include "ParticleSplash.h"
#include "Engine.h"

void ParticleSplash::onTick(){
	location += engine::random.direction();
}