#pragma once
#include "Particle.h"

class ParticleSpark : public Particle
{
public:
	void Particle::onTick();
	std::shared_ptr<Particle> Particle::clone() override;

	ParticleSpark(Glyph glyph, int tickRate, int ageMax) :
		Particle(glyph, tickRate, ageMax){}
};

