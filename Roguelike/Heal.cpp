#include "Heal.h"

void Heal::update(DynamicObject &dynamicObject){
	dynamicObject.health += amount;
	if (dynamicObject.health > dynamicObject.healthMax) dynamicObject.health = dynamicObject.healthMax;
}