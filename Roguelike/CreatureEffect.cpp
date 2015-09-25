#include "CreatureEffect.h"
#include "Engine.h"
#include <algorithm>

CreatureEffect::CreatureEffect(std::string name, double modifier, double durationFromMax, 
	StatType statType, std::shared_ptr<VisualEffect> visualEffectOnApply) :
	name(name),
	modifier(modifier),
	duration(std::max((int)(engine::effectDurationBase * durationFromMax), 1)),
	statType(statType),
	visualEffectOnApply(visualEffectOnApply){
}

void CreatureEffect::apply(Creature &creature){
	engine::visualEffectPlayer.playEffect(creature.location, visualEffectOnApply);
	--duration;
}
