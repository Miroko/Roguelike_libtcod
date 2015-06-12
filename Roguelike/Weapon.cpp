#include "Weapon.h"

std::string Weapon::getDescription(){
	return Item::getDescription() + " " + std::to_string(damage);
}