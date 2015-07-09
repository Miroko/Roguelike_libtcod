#pragma once
#include "ParticleEffect.h"
#include "ParticleSpiralUp.h"

class EffectSmoke : public ParticleEffect
{
public:
	EffectSmoke(Point2D &location) : ParticleEffect({
		std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkGrey), location, 2, 60)),
		std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkerGrey), location, 3, 60)),
		std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkerGrey), location, 5, 60)) }){};
};

