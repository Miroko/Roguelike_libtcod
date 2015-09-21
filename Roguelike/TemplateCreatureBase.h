#pragma once
#include "CreatureLimb.h"
#include <vector>
#include <string>

class TemplateCreatureBase
{
public:
	std::vector<CreatureLimb> limbs;
	std::shared_ptr<VisualEffect> visualEffectOnTakeDamage;

	TemplateCreatureBase(std::vector<CreatureLimb> limbs, std::shared_ptr<VisualEffect> visualEffectOnTakeDamage) :
		limbs(limbs),
		visualEffectOnTakeDamage(visualEffectOnTakeDamage){}
	TemplateCreatureBase(){}
};

