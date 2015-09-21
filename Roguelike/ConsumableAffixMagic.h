#pragma once
#include "RarityAffixConsumable.h"
#include "CreatureEffectMagic.h"
#include "VisualEffect.h"
#include "ParticleSpiralUp.h"

class ConsumableAffixMagic : public RarityAffixConsumable
{
public:
	std::string RarityAffixConsumable::getDescription(GameObject &ownerObject);

	ConsumableAffixMagic(std::string name, double modifier, double durationFromMax) :
		RarityAffixConsumable(name, std::shared_ptr<CreatureEffect>(new CreatureEffectMagic(
		name,
		modifier,
		durationFromMax,
		std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
		std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkHan), 2, 10)) })
			)))){}
};

