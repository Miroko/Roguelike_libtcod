#pragma once
#include "Particle.h"

class ParticleSplash : public Particle
{
public:
	void Particle::onTick();

	ParticleSplash(Glyph glyph, Point2D location, int tickRate, int ageMax) : Particle(glyph, location, tickRate, ageMax){}
};

