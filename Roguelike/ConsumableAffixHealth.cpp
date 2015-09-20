#include "ConsumableAffixHealth.h"
#include "Consumable.h"
#include "Engine.h"
#include <algorithm>

std::string ConsumableAffixHealth::getDescription(GameObject &ownerObject){
	Consumable &ownerConsumable = static_cast<Consumable&>(ownerObject);
	return
		"Health " +
		engine::string.value(engine::healthMax * effect->modifier * ownerConsumable.potency) +
		" for " + engine::string.duration(std::max((int)(effect->duration * ownerConsumable.concentration), 1));
}
