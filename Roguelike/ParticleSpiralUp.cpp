#include "ParticleSpiralUp.h"
#include "Engine.h"
#include "Direction.h"

void ParticleSpiralUp::onTick(){
	float directionRoll = engine::random.generator->getFloat(0.0f, 1.0f);
	if (directionRoll < 0.25f) location += LEFT;
	else if (directionRoll < 0.75f) location += UP;
	else if (directionRoll <= 1.00f) location += RIGHT;
}