#include "WeaponAffixDamage.h"
#include "Weapon.h"
#include "Engine.h"

std::string WeaponAffixDamage::getDescription(GameObject &ownerObject){
	Weapon &ownerWeapon = static_cast<Weapon&>(ownerObject);
	return "Damage " + engine::string.value((int)(ownerWeapon.getDamageBase() * getDamageModifier()));
}