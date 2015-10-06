#pragma once
#include "RarityType.h"
#include <memory>

class RarityMod
{
public:
	RarityType *rarityType;
	std::vector<RarityAffix*> rarityAffixes;

	RarityAffix* getAffixPre();
	RarityAffix* getAffixPost();

	RarityMod(RarityType &rarityType, std::vector<RarityAffix*> rarityAffixes = {}) :
		rarityType(&rarityType),
		rarityAffixes(rarityAffixes){}

	RarityMod(){}
};

