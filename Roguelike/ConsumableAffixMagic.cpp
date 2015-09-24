#include "ConsumableAffixMagic.h"
#include "Consumable.h"
#include "Engine.h"
#include <algorithm>

std::string ConsumableAffixMagic::getDescription(GameObject &ownerObject){
	Consumable &ownerConsumable = static_cast<Consumable&>(ownerObject);
	return
		"Magic " +
		engine::string.value(engine::magicMax * effect->modifier * ownerConsumable.potency) +
		" for " + engine::string.duration(std::max((int)(effect->duration * ownerConsumable.concentration), 1));
}
