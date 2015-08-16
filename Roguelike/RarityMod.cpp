#include "RarityMod.h"

RarityAffix* RarityMod::getAffixPre(){
	if (rarityAffixes.size() >= 1){
		return rarityAffixes.at(0);
	}
	else return nullptr;
}

RarityAffix* RarityMod::getAffixPost(){
	if (rarityAffixes.size() >= 2){
		return rarityAffixes.at(1);
	}
	else return nullptr;
}
