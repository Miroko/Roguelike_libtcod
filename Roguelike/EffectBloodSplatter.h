#pragma once
#include "ParticleEffect.h"
#include "ParticleSplash.h"

class EffectBloodSplatter : public ParticleEffect
{
public:
	EffectBloodSplatter(Point2D &location) : ParticleEffect({
		std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::darkerRed), location, 3, 9)),
		std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::darkRed), location, 2, 6)) }){};
};

