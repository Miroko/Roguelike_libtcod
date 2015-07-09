#pragma once
#include "Particle.h"

class ParticleSpark : public Particle
{
public:
	void Particle::onTick();

	ParticleSpark(Glyph glyph, Point2D location, int tickRate, int ageMax) : Particle(glyph, location, tickRate, ageMax){}
};

