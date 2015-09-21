#pragma once
#include "Particle.h"

class ParticleSplash : public Particle
{
public:
	void Particle::onTick() override;
	std::shared_ptr<Particle> Particle::clone() override;

	ParticleSplash(Glyph glyph, int tickRate, int ageMax) :
		Particle(glyph, tickRate, ageMax){}
};

