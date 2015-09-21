#pragma once
#include "OperatableObject.h"
#include "VisualEffect.h"
#include "ParticleSpark.h"

class Anvil : public OperatableObject
{
public:
	std::shared_ptr<OperatableObject> copy();

	Anvil() :
		OperatableObject(DynamicObject(GameObject(
		"Anvil",
		GameObject::ANVIL, 
		Glyph(TCODColor::darkerGrey, TCODColor::darkGrey, 'A')),
		9999),
		std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
			std::shared_ptr<Particle>(new ParticleSpark(Glyph(TCODColor::yellow), 1, 3)),
			std::shared_ptr<Particle>(new ParticleSpark(Glyph(TCODColor::amber), 1, 1)) })
		)){}
};

