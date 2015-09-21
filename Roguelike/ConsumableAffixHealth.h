#pragma once
#include "RarityAffixConsumable.h"
#include "CreatureEffectHealth.h"
#include "VisualEffect.h"
#include "ParticleSpiralUp.h"

class ConsumableAffixHealth : public RarityAffixConsumable
{
public:
	std::string RarityAffixConsumable::getDescription(GameObject &ownerObject);

	ConsumableAffixHealth(std::string name, double modifier, double durationFromMax) :
		RarityAffixConsumable(name, std::shared_ptr<CreatureEffect>(new CreatureEffectHealth(
		name, 
		modifier, 
		durationFromMax,
		std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
			std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkestGreen), 2, 10)) })
		)))){}
};

