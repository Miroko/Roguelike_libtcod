#pragma once
#include "OperatableObject.h"
#include "VisualEffect.h"
#include "ParticleSpiralUp.h"

class AlchemyTable : public OperatableObject
{
public:
	std::shared_ptr<OperatableObject> copy();

	AlchemyTable(std::string name, Glyph glyph) :
		OperatableObject(DynamicObject(GameObject(
		name,
		GameObject::ALCHEMY_TABLE,
		glyph),
		100),
		std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
			std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkViolet), 2, 20)),
			std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkerSea), 2, 20)),
			std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkGrey), 3, 30)) })
		)){}
};

