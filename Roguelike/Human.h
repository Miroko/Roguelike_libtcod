#pragma once
#include "AliveObject.h"

class Human : public AliveObject
{
	
public:	
	static Loot loot;
	Human(std::string name) : AliveObject(Glyph(TCODColor::lighterAmber, '@'), name, MEDIUM, &loot){};
	Human();
};