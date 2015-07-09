#include "ParticleSpark.h"
#include "Engine.h"

void ParticleSpark::onTick(){
	location += engine::random.direction();
}
