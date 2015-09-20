#pragma once
#include "RarityAffixAccessory.h"

class CreatureSkill;
class AccessoryAffixSkill : public RarityAffixAccessory
{
private:
	double skillModifier;
	CreatureSkill &skill;

public:
	CreatureSkill* getSkill() override { return &skill; }
	double getProfiencyModifier() override { return skillModifier; }
	std::string RarityAffix::getDescription(GameObject &ownerObject) override;

	AccessoryAffixSkill(std::string name, double skillModifier, CreatureSkill &skill) :
		RarityAffixAccessory(name),
		skillModifier(skillModifier),
		skill(skill){}
};

