#include "DynamicObject.h"
#include "StaticObject.h"
#include "iostream"

bool DynamicObject::isBlockedBy(DynamicObject &object){
	if (this->size == SMALL) return false;
	else{
		return true;
	}
}

void DynamicObject::takeDamage(int amount){
	health -= amount;
	std::cout << this->name << health << "\n";
	if (health <= 0){
		std::cout << "dead " << "\n";
	}
}