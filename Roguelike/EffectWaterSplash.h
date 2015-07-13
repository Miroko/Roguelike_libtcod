#pragma once
#include "ParticleEffect.h"
#include "ParticleSplash.h"

class EffectWaterSplash : public ParticleEffect
{
public:
	EffectWaterSplash(Point2D &location) : ParticleEffect({
		std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::lightBlue), location, 2, 6)),
		std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::lightBlue), location, 3, 6)),
		std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::darkBlue), location, 4, 4)) }){};
};

