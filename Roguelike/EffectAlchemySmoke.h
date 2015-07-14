#pragma once
#include "ParticleEffect.h"
#include "ParticleSpiralUp.h"

class EffectAlchemySmoke : public ParticleEffect
{
public:
	EffectAlchemySmoke(Point2D &location) : ParticleEffect({
		std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkViolet), location, 2, 20)),
		std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkerSea), location, 2, 20)),
		std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkGrey), location, 3, 30)) }){};
};

