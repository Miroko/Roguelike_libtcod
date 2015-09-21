#pragma once
#include "OperatableObject.h"
#include "VisualEffect.h"
#include "ParticleSpiralUp.h"
#include <vector>
class Forge : public OperatableObject
{
public:
	std::shared_ptr<OperatableObject> copy();

	Forge() :
		OperatableObject(DynamicObject(GameObject(
		"Forge",
		GameObject::FORGE,
		Glyph(TCODColor::darkerGrey, TCODColor::darkRed, 'F')),
		9999),
		std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
			std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkGrey), 2, 60)),
			std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkerGrey), 3, 60)),
			std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkerGrey), 5, 60)) }))
		){}
};

