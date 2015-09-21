#pragma once
#include "RarityAffixConsumable.h"
#include "CreatureEffectStamina.h"
#include "VisualEffect.h"
#include "ParticleSpiralUp.h"

class ConsumableAffixStamina : public RarityAffixConsumable
{
public:
	std::string RarityAffixConsumable::getDescription(GameObject &ownerObject);

	ConsumableAffixStamina(std::string name, double modifier, double durationFromMax) :
		RarityAffixConsumable(name, std::shared_ptr<CreatureEffect>(new CreatureEffectStamina(
		name, 
		modifier, 
		durationFromMax, 
		std::shared_ptr<VisualEffect>(new VisualEffect(std::vector<std::shared_ptr<Particle>>{
			std::shared_ptr<Particle>(new ParticleSpiralUp(Glyph(TCODColor::darkestCyan), 2, 10)) }))
		))){}
};
