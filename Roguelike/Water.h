#pragma once
#include "Tile.h"
#include "VisualEffect.h"
#include "ParticleSplash.h"

class Water : public Tile
{
public:
	Water(std::string name, Glyph glyph) :
		Tile(GameObject(
		name, 
		GameObject::WATER, 
		glyph),
		true, 
		20.0f,
		std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
			std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::lightBlue), 2, 6)),
			std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::lightBlue), 3, 6)),
			std::shared_ptr<Particle>(new ParticleSplash(Glyph(TCODColor::darkBlue), 4, 4))	}))
		){}
};

