#pragma once
#include "ParticleEffect.h"
#include "ParticleSpark.h"

class EffectSparkles : public ParticleEffect
{
public:
	EffectSparkles(Point2D &location) : ParticleEffect({
		std::shared_ptr<Particle>(new ParticleSpark(Glyph(TCODColor::yellow), location, 1, 3)),
		std::shared_ptr<Particle>(new ParticleSpark(Glyph(TCODColor::amber), location, 1, 1)) }){};
};

