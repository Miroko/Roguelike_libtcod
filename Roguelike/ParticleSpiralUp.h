#pragma once
#include "Particle.h"

class ParticleSpiralUp : public Particle
{
public:
	void Particle::onTick();
	std::shared_ptr<Particle> Particle::clone() override;

	ParticleSpiralUp(Glyph glyph, int tickRate, int ageMax) :
		Particle(glyph, tickRate, ageMax){}
};

