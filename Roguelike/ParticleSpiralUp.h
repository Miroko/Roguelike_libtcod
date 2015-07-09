#pragma once
#include "Particle.h"

class ParticleSpiralUp : public Particle
{
public:
	void Particle::onTick();

	ParticleSpiralUp(Glyph glyph, Point2D location, int tickRate, int ageMax) : Particle(glyph, location, tickRate, ageMax){}
};

